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

	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return 0;
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return 0;
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return 0;
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	return nullptr;
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
				break;

			}

			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;
	
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

				LastNamePair pair;

				pair.Lastname = lastName;
				pair.probability = count / 100'000.0f;

				m_lastNames.Emplace(pair);

				break;

			

			}

			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;
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