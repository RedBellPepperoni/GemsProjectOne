#include "cSnotify.h"
#include "cMusicGenerator.h"
#include "cPersonGenerator.h"



//// This returns a COPY of the users library, in the form of a regular dynamic array.
//bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary);
//{
//	// The caller would do something like this (assume the user ID = 28472382)
//	//
//	//	cSong* pTheSongs = 0;
//	//	unsigned int arraySize = 0;
//	//	GetUsersSongLibrary( 28472382, pTheSongs, arraySize );
//	// 
//	// Inside this method, you'd do something like this:
//
//	// TODO: Find that user... 
//
//	// Alloate a heap based array to hold all the songs...
//
////	sizeOfLibary = WhateverYouHaveToDoToGetThisValue();
////	pCopyOfLibrary = new cSong[sizeOfLibary];
//
//	// The array and the size of the array are "returned" by reference to the caller. 
//
//	// TODO: Copy all the songs over
//
//	return true;
//}

cSnotify::cSnotify()
{
	// initialize the Pointers
	m_musicGenerator = std::make_shared<cMusicGenerator>();

}

cSnotify::~cSnotify()
{
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	cHashElement<int, cPerson*>* iterator = m_userList.Find(pPerson->GetSIN());
	
	if (iterator == nullptr)
	{
		m_userList.Add(pPerson->GetSIN(), pPerson);
		return true;
	}

		
	errorString = "Snotify : Cannot Add : User Already Exists, ";
	return false;


	
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{



	cHashElement<int, cPerson*>* iterator = m_userList.Find(pPerson->GetSIN());

	if (iterator == nullptr)
	{
		errorString = "Snotify : Couldn't Find User";
		return false;
	}


	iterator->value->age = pPerson->age;
	iterator->value->city = pPerson->city;
	iterator->value->first = pPerson->first;
	iterator->value->gender = pPerson->gender;
	iterator->value->last = pPerson->last;
	iterator->value->streetDirection = pPerson->streetDirection;
	iterator->value->streetName = pPerson->streetName;
	iterator->value->streetNumber = pPerson->streetNumber;

	return true;
	
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	return false;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	return false;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	return false;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	return false;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	return nullptr;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	return false;
}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	return false;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	cHashElement<int, cPerson*>* iterator = m_userList.Find(SIN);

	if (iterator == nullptr)
	{
		printf("Snotify : Couldn't Find User with SIN :[%d] ",SIN);
		return nullptr;
	}

	return iterator->value;


}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	return nullptr;
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	return nullptr;
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	return nullptr;
}

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return false;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return false;
}

bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return false;
}

bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return false;
}

bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return false;
}

bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return false;
}



void cSnotify::LoadMusicDataBase()
{
	std::string errorString;

	if (m_musicGenerator->LoadMusicInformation(musicFilePath, errorString))
	{
		printf("\n----------------------------------------------------\n");
	}

	else
	{
		printf(errorString.c_str());
	}
}
