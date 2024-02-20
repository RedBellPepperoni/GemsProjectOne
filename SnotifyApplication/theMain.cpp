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
static std::string musicFilePath = "Data\\hot_stuff_2.csv";

 
static cPersonGenerator personGenerator;
static cMusicGenerator musicGenerator;

void LoadPersonData()
{
	
	std::string errorString = std::string();

	if(!personGenerator.LoadCensusFiles(babyNameFilePath,lastNameFilePath, streetNameFilePath,errorString))
	{
		printf(errorString.c_str());
	}

}

void LoadMusicData()
{
	std::string errorString = std::string();

	if (!musicGenerator.LoadMusicInformation(musicFilePath, errorString))
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

	LoadMusicData();

	musicGenerator;
	
}