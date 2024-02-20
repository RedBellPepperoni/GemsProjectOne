#include "cSnotify.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include <string.h>

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

	

	std::string errorString;

	cSong* oldSong1 = musicGenerator->getRandomSong();
	cSong* oldSong2 = musicGenerator->getRandomSong();
	cSong* oldSong3 = musicGenerator->getRandomSong();
	cSong* oldSong4 = musicGenerator->getRandomSong();
	cSong* oldSong5 = musicGenerator->getRandomSong();

	snotify->AddSong(oldSong1,errorString);
	snotify->AddSong(oldSong2,errorString);
	snotify->AddSong(oldSong3,errorString);
	snotify->AddSong(oldSong4,errorString);
	snotify->AddSong(oldSong5,errorString);

	cSong* oldSong10 = snotify->FindSong(oldSong1->getUniqueID());
	cSong* oldSong20 = snotify->FindSong(oldSong2->getUniqueID());
	cSong* oldSong30 = snotify->FindSong(oldSong3->getUniqueID());
	cSong* oldSong40 = snotify->FindSong(oldSong4->getUniqueID());
	cSong* oldSong50 = snotify->FindSong(oldSong5->getUniqueID());




}