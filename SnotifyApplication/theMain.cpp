#include "cSnotify.h"
#include "cPersonGenerator.h";
#include <string.h>

int main(int argc, char* argv)
{	
	//Creating a Person Generator
	std::shared_ptr<cPersonGenerator> personGenerator = std::make_shared<cPersonGenerator>();
	// Update Peron data file paths
	personGenerator->UpdateFirstNameFilePath("Data\\yob2010.txt");
	personGenerator->UpdateLastNameFilePath("Data\\Names_2010Census.csv");
	personGenerator->UpdateStreetNameFilePath("Data\\Street_Names.csv");

	personGenerator->LoadPersonData();

	// Create a new snotify class
	std::shared_ptr<cSnotify> snotify = std::make_shared<cSnotify>(); 

	// Update the Data file paths Here
	snotify->UpdateMusicFilePath("Data\\hot_stuff_2.csv"); 

	// Load all the data from the === Usually please call these function once per snotify class
	snotify->LoadMusicDataBase(); 


	std::string errorString;

	cPerson* newPerson = personGenerator->generateRandomPerson();

	std::string old_name = newPerson->first;

	if (!snotify->AddUser(newPerson, errorString))
	{
		printf(errorString.c_str());
	}


	newPerson->first = "LEEEEEEEEEEEEEEEEEEEEEEEEEEEROY JENKINS";

	//if (!snotify->AddUser(personGenerator->generateRandomPerson(), errorString))
	//{
	//	printf(errorString.c_str());
	//}

	//if (!snotify->AddUser(personGenerator->generateRandomPerson(), errorString))
	//{
	//	printf(errorString.c_str());
	//}

	snotify->getUserList();
	
	cPerson* person = snotify->FindUserBySIN(newPerson->GetSIN());

	

}