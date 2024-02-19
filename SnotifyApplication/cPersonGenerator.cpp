#include "cPersonGenerator.h"
#include "cFile.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>

cPersonGenerator::cPersonGenerator()
{
}

cPersonGenerator::~cPersonGenerator()
{
}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{
	
	if (!LoadFirstNames(babyNameFile, errorString))
	{
		return false;
	}

	if (!LoadLastNames(surnameFile, errorString))
	{
		return false;
	}

	if (!LoadStreatNames(streetNameFile, errorString))
	{
		return false;
	}

	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return m_firstNamesFemale.Size() + m_firstNamesMale.Size() + m_firstNamesNoPref.Size();
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return m_lastNames.Size();
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return 0;
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	// Create a new Person on Heap
	cPerson* person = new cPerson();
	//cPerson* person = std::make_shared<cPerson>().get();

	//==== Generate a Random Gender ( only Randomizing between Female / male and non_binary ) ==========
	person->gender = (cPerson::eGenderType)cRandom::Range(0,2);

	// ======== generate the First and Last name =========================
	person->first = GetRandomFirstName(person->gender);
	person->last = GetRandomLastName();


	StreetData randomStreetData = GetRandomStreetAddress();
	person->streetName = randomStreetData.StreetName;
	person->streetType = randomStreetData.StreetType;
	person->streetDirection = randomStreetData.PostDirection;

	return person;
}

bool cPersonGenerator::LoadFirstNames(const std::string& path, std::string& errorMsg)
{
	if (!cFile::FileExists(path))
	{
		errorMsg = "Person Generator : Couldn't load Baby names : [File not found]";
		return false;
	}

	//            that someone is named "Smith"
	std::ifstream namesFile(path);
	std::string theLine;

	unsigned int lineCount = 0;
	unsigned int loadCount = 0;

	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;

		std::string babyName;

		while (std::getline(ssLine, token, ','))
		{

			

			switch (tokenCount)
			{
				// The actual name
			case 0: babyName = token;
				break;

				//The gender
			case 1: 

				// Load name in Male Data container
				if (token == "M")
				{
					m_firstNamesMale.Emplace(babyName);
				}
				// Load name into Female data container
				else if (token == "F")
				{
					m_firstNamesFemale.Emplace(babyName);
				}

				// Otherwise just store in the NoPref
				else
				{
					m_firstNamesNoPref.Emplace(babyName);
				}

				loadCount++;
				break;

			}

			tokenCount++;
		}
	}

	printf("Person Generator : Loaded [%d] / [%d]First Names \n",loadCount, lineCount);
	
}

bool cPersonGenerator::LoadLastNames(const std::string& path, std::string& errorMsg)
{
	if (!cFile::FileExists(path))
	{
		errorMsg = "Person Generator : Couldn't load Last names : [File not found]";
		return false;
	}

	//            that someone is named "Smith"
	std::ifstream namesFile(path);
	std::string theLine;

	unsigned int lineCount = 0;
	unsigned int loadCount = 0;

	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;

		std::string lastName;

		//If its the first 
		if (lineCount == 1)
		{
			continue;
		}


		while (std::getline(ssLine, token, ','))
		{
			
			switch (tokenCount)
			{
				// The actual name
			case 0: lastName = token;
				break;

				//The number per 100K
			case 3:
				// Convert the string to a float value
				float count = std::stof(token);

				LastNameData pair;

				pair.LastName = lastName;
				pair.Probability = count / 100'000.0f;

				m_lastNames.Emplace(pair);


				loadCount++;
				break;

			

			}

			tokenCount++;
		}
	}

	printf("Person Generator : Loaded [%d]/[%d] Last Names \n",loadCount, lineCount - 1);
}

bool cPersonGenerator::LoadStreatNames(const std::string& path, std::string& errorMsg)
{
	if (!cFile::FileExists(path))
	{
		errorMsg = "Person Generator : Couldn't load Street Addresses : [File not found]";
		return false;
	}

	
	std::ifstream namesFile(path);
	std::string theLine;

	unsigned int lineCount = 0;
	unsigned int loadCount = 0;
	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;

		std::string streetName;
		std::string streetType;
		std::string postDirection;

		//If its the first 
		if (lineCount == 1)
		{
			continue;
		}


		while (std::getline(ssLine, token, ','))
		{

			switch (tokenCount)
			{
				// The strrt name
			case 1: streetName = token;
				break;

			case 2:
				streetType = token;
				break;

			case 3: 
				postDirection = token;
		

			}

		

			tokenCount++;
		}

		StreetData streetData;

		streetData.StreetName = streetName;
		streetData.StreetType = streetType;
		streetData.PostDirection = postDirection.empty() ? GetRandomPostDirection() : postDirection;

		m_streetNames.Emplace(streetData);
		loadCount++;

	}

	printf("Person Generator : Loaded [%d]/[%d] Street addresses \n",loadCount, lineCount);
}

std::string cPersonGenerator::GetRandomPostDirection() 
{
	int randomDirectionIndex = cRandom::Range(0,3);

	switch (randomDirectionIndex)
	{
	case 0: return "NORTH";
		break; 
	case 1: return "EAST";
		break;
	case 2: return "WEST";
		break;

	case 3: 
		// fall condition
	default: return "SOUTH";
		break;
	}
}

const std::string cPersonGenerator::GetRandomFirstName(const cPerson::eGenderType& gender) const
{

	int randomFirstNameIndex = 0;
	int randomContainerIndex = 2;

	switch (gender)
	{
	case cPerson::eGenderType::FEMALE: 

		// Gather a random Female name and return it
		randomFirstNameIndex = cRandom::Range(0, (int32_t)m_firstNamesFemale.Size() - 1);
		return m_firstNamesFemale[randomFirstNameIndex];
		break;

	case cPerson::eGenderType::MALE :

		// Gather a random Male name and return it
		randomFirstNameIndex = cRandom::Range(0, (int32_t)m_firstNamesMale.Size() - 1);
		return m_firstNamesMale[randomFirstNameIndex];
		break;

	case cPerson::eGenderType::NON_BINARY: 

		// get what data container should be accesses  : since Non binary can pull from any name List
		randomContainerIndex = cRandom::Range(0, 2);

		switch (randomContainerIndex)
		{
			// Get a Female Names
		case 0:  // Gather a random Female name and return it

			randomFirstNameIndex = cRandom::Range(0, m_firstNamesFemale.Size() - 1);
			return m_firstNamesFemale[randomFirstNameIndex];
			break;

			//get a Male name
		case 1: // Gather a random Male name and return it
			
			randomFirstNameIndex = cRandom::Range(0, m_firstNamesMale.Size() - 1);
			return m_firstNamesMale[randomFirstNameIndex];
			break;

			// Get a No Pref name
		case 2:
			
			randomFirstNameIndex = cRandom::Range(0, m_firstNamesNoPref.Size() - 1);
			return m_firstNamesNoPref[randomFirstNameIndex];
			break;

		default:
			break;
		}

	default: 
		break;
	}

	
}

const std::string cPersonGenerator::GetRandomLastName() const
{
	//https://stackoverflow.com/questions/8529665/changing-probability-of-getting-a-random-number

	float distributedpercentage = cRandom::Range(0.0f, 1.0f);
	float currentcumulative = 0;

	for (int i = m_lastNames.Size() -1; i >= 0 ; i--)
	{
		LastNameData data = m_lastNames[i];
		currentcumulative += data.Probability;

		if (distributedpercentage < currentcumulative )
		{
			return  m_lastNames[i].LastName;
		}
		else
		{
			if (i == 0)
			{
				return m_lastNames[0].LastName;
			}
		}
	}

}

const StreetData cPersonGenerator::GetRandomStreetAddress() const
{
	int randomStreetIndex = cRandom::Range(0, m_streetNames.Size() - 1);
	return m_streetNames[randomStreetIndex];
}



// Here's a simple way to load the comma delimited files:
bool readCSVFile(void)
{
	// Open the file
	std::ifstream namesFile("Names_2010Census.csv");
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				std::cout << token << std::endl;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}