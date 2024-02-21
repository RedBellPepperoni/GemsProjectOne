#include "cSnotify.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include <string.h>

static std::string errorString;

#define _CHECK(condition) \
	if(!condition) \
	{printf(errorString.c_str());}\
	else\
	condition


int main(int argc, char* argv)
{	
	// The Safe pointers to each of the generator class
	std::shared_ptr<cPersonGenerator> personGenerator = std::make_shared<cPersonGenerator>();
	std::shared_ptr<cMusicGenerator> musicGenerator = std::make_shared<cMusicGenerator>();


	// Update Peron data file paths
	personGenerator->UpdateFirstNameFilePath("Data\\yob2010.txt");
	personGenerator->UpdateLastNameFilePath("Data\\Names_2010Census.csv");
	personGenerator->UpdateStreetNameFilePath("Data\\Street_Names.csv");
	personGenerator->LoadPersonData();


	musicGenerator->UpdateMusicFilePath("Data\\hot_stuff_2.csv");
	musicGenerator->LoadMusicDataBase();

	// Create a new snotify class
	std::shared_ptr<cSnotify> snotify = std::make_shared<cSnotify>(); 

	// Finding a song on a bigger Data set
	cSong* song =  musicGenerator->findSong("Carrie", "Europe");

	//Finding a song that doesnt exist
	cSong* songMew =  musicGenerator->findSong("..", "yees");


	//std::string errorString;

	cSong* oldSong1 = musicGenerator->getRandomSong();
	cSong* oldSong2 = musicGenerator->getRandomSong();
	cSong* oldSong3 = musicGenerator->getRandomSong();
	cSong* oldSong4 = musicGenerator->getRandomSong();
	cSong* oldSong5 = musicGenerator->getRandomSong();

	cPerson* person1 = personGenerator->generateRandomPerson();
	cPerson* person2 = personGenerator->generateRandomPerson();
	cPerson* person3 = personGenerator->generateRandomPerson();
	cPerson* person4 = personGenerator->generateRandomPerson();
	cPerson* person5 = personGenerator->generateRandomPerson();
	cPerson* person6 = personGenerator->generateRandomPerson();

	if (!snotify->AddSong(oldSong1, errorString))
	{
		printf(errorString.c_str());
	}

	_CHECK(snotify->AddSong(oldSong2,errorString));
	_CHECK(snotify->AddSong(oldSong3,errorString));
	_CHECK(snotify->AddSong(oldSong4,errorString));
	_CHECK(snotify->AddSong(oldSong5,errorString));



	_CHECK(snotify->AddUser(person1, errorString));
	_CHECK(snotify->AddUser(person2, errorString));
	_CHECK(snotify->AddUser(person4, errorString));
	_CHECK(snotify->AddUser(person5, errorString));
	_CHECK(snotify->AddUser(person1, errorString));


	cPerson* persontest1snotify = snotify->FindUserBySnotifyID(person1->getSnotifyUniqueUserID());
	cPerson* persontest1Sin = snotify->FindUserBySIN(person1->GetSIN());
	


	snotify->AddSongToUserLibrary(person1->getSnotifyUniqueUserID(),oldSong2,errorString);
	snotify->AddSongToUserLibrary(person1->getSnotifyUniqueUserID(),oldSong3,errorString);
	snotify->AddSongToUserLibrary(person1->getSnotifyUniqueUserID(),oldSong4,errorString);

	
	cPerson* user = snotify->FindUserBySnotifyID(person1->getSnotifyUniqueUserID());



}