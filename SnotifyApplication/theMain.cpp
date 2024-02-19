#include "cVector.h"

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


int main(int argc, char* argv)
{
	
	LoadPersonData();

	personGenerator;


}