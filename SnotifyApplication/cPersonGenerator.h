#ifndef _cPersonGenerator_HG_
#define _cPersonGenerator_HG_

#include <string>
#include "cPerson.h"
#include "cVector.h"
#include "cRandom.h"

struct LastNameData
{
	std::string LastName;
	float Probability;
};


struct StreetData
{
	std::string StreetName;
	std::string StreetType;
	std::string PostDirection;
};


class cPersonGenerator
{
public:
	cPersonGenerator();
	~cPersonGenerator();

	// This takes three files:
	// - One of the "Popular Baby Names" found here: https://www.ssa.gov/oact/babynames/limits.html
	//   (example: "yob2001.txt" which are babies born in the year 2001
	// - The "Names_2010Census.csv" file, from:
	//   "Frequently Occurring Surnames from the 2010 Census" from here:
	//   https://www.census.gov/topics/population/genealogy/data/2010_surnames.html
	// - The "Street_Names.csv" file, from:
	//   "Street Names (San Francisco)" from here: 
	//   https://catalog.data.gov/dataset/street-names-37fec/resource/d655cc82-c98f-450a-b9bb-63521c870503
	// Returns:
	// - true of successful
	// - false if there's any issue (can't find file, or whatever)
	//   If false, then the "errorString" (passed by reference) should be loaded with some sort of 
	//   description of what went wrong (file didn't open, parse issue, Skynet became self aware, etc.)
	//   Use your discretion (and creativity) for this. 
	bool LoadCensusFiles(
		std::string babyNameFile,
		std::string surnameFile,
		std::string streetNameFile,
		std::string& errorString);

	unsigned int getNumberOfNamesLoaded(void);
	unsigned int getNumberOfSurnamesLoaded(void);
	unsigned int getNumberOfStreetsLoaded(void);

	// Randomly generates a person from the data
	// Returns 0, NULL, or nullptr if it can't do this. 
	cPerson* generateRandomPerson(void);

private:

	bool LoadFirstNames(const std::string& path, std::string& errorMsg);
	bool LoadLastNames(const std::string& path, std::string& errorMsg);
	bool LoadStreatNames(const std::string& path, std::string& errorMsg);

	std::string GetRandomPostDirection();

	const std::string GetRandomFirstName(const cPerson::eGenderType& gender) const;
	const std::string GetRandomLastName() const;
	const StreetData GetRandomStreetAddress() const;



private:

	// ============ The storage for First names (according to gender) =============
	
	cVector<std::string> m_firstNamesFemale;
	cVector<std::string> m_firstNamesMale;
	cVector<std::string> m_firstNamesNoPref;


	// ============ Teh Storage for Last names and the Probabilities ==============
	cVector<LastNameData> m_lastNames;

	// ============= Teh Storage for Street Data (name, Type and Post Direction)
	cVector<StreetData> m_streetNames;


	cVector<cPerson*> m_personDatabase;
};


#endif 
