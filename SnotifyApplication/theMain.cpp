#include "cVector.h"
#include "cHashMap.h"
#include "cMusicGenerator.h"
#include "cPerson.h"
#include "cPersonGenerator.h"
#include "cSnotify.h"
#include "cSong.h"

static std::string babyNameFilePath = "Data\\yob2010.txt";
static std::string lastNameFilePath = "Data\\Names_2010Census.csv";
static std::string streetNameFilePath = "Data\\Street_Names.csv";

 
static cPersonGenerator personGenerator;

void LoadPersonData()
{
	
	std::string errorString = std::string();

	if(!personGenerator.LoadCensusFiles(babyNameFilePath,lastNameFilePath, streetNameFilePath,errorString))
	{
		printf(errorString.c_str());
	}

	

}

struct Song
{
	std::string name;
	int id;
};




int main(int argc, char* argv)
{
	// Load all the Database files 
	LoadPersonData();

	cHashMap<std::string, Song> testMap;

	Song song;
	song.name = "ShakeitOff";
	song.id = 22;

	testMap.Add("Pepper",song);



	/*cPerson* randomPersoneOne = personGenerator.generateRandomPerson();
	cPerson* randomPersoneTwo = personGenerator.generateRandomPerson();
	cPerson* randomPersoneThree = personGenerator.generateRandomPerson();
	cPerson* randomPersoneFour = personGenerator.generateRandomPerson();
	cPerson* randomPersoneFive = personGenerator.generateRandomPerson();*/

	//delete randomPersoneOne;
	//delete randomPersoneTwo;
	//delete randomPersoneThree;
	//delete randomPersoneFour;
	//delete randomPersoneFive;

	testMap;

	cHashElement<std::string, Song>* iterator = testMap.Find("Beedo");
	const cHashElement<std::string, Song>* iteratorTwo = testMap.Find("Pepper");

	if (iterator)
	{
		Song newsong = iterator->value;
	}

	Song newsong = testMap["Pepper"];

	
}