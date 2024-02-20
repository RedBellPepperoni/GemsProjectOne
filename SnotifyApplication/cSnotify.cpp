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
	

}

cSnotify::~cSnotify()
{
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	cHashElement<int, cPerson*>* iterator = m_userListSIN.Find(pPerson->GetSIN());

	
	
	if (iterator == nullptr)
	{
		// Add to Both maps (High Space complexity but very low timecomplexity)
		m_userListSIN.Add(pPerson->GetSIN(), pPerson);
		m_snotifyIDToSIN.Add(pPerson->getSnotifyUniqueUserID(), pPerson->GetSIN());

		std::shared_ptr<SnotifyUser> user = std::make_shared<SnotifyUser>();
		user->userId = pPerson->getSnotifyUniqueUserID();


		m_UserSongDictionary.Emplace(user);
		return true;
	}

	//// Update values incase of Deleted Error
	//if (iterator->value == nullptr)
	//{
	//	iterator->value = pPerson;
	//	m_snotifyIDToSIN[pPerson->getSnotifyUniqueUserID()] = pPerson->GetSIN();
	//	return true;
	//}

	
	errorString = "Snotify[AddUser]: User Already Exists \n";
	return false;


	
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{

	cHashElement<int, cPerson*>* iterator = m_userListSIN.Find(pPerson->GetSIN());

	if (iterator == nullptr)
	{
		errorString = "Snotify[UpdateUser]: Couldn't Find User\n";
		return false;
	}


	iterator->value = pPerson;
	m_snotifyIDToSIN[pPerson->getSnotifyUniqueUserID()] = pPerson->GetSIN();

	return true;
	
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	cHashElement<int, int>* iterator = m_snotifyIDToSIN.Find(SnotifyUserID);

	if (iterator == nullptr)
	{
		errorString = "Snotify[DeleteUser]: NO User to Delete\n";
		return false;
	}

	int SIN = iterator->value;
	cPerson* perosn = m_userListSIN.Find(SIN)->value;
	m_snotifyIDToSIN.Remove(SnotifyUserID);

	for (int i = 0; i < m_UserSongDictionary.Size(); i++)
	{
		if (m_UserSongDictionary[i]->userId == SnotifyUserID)
		{
			m_UserSongDictionary[i] = m_UserSongDictionary.Back();
			m_UserSongDictionary.Pop();

			break;
		}

	}

	m_userListSIN.Remove(SIN);

	delete perosn;
	perosn = nullptr;

}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	if (pSong == nullptr) 
	{
		errorString = "Snotify[AddSong]: song is null\n"; 
		return false;
	}

	cHashElement<int, cSong*>* iterator = m_songsList.Find(pSong->getUniqueID());

	if (iterator == nullptr)
	{
		// Add to Both maps (High Space complexity but very low timecomplexity)
		m_songsList.Add(pSong->getUniqueID(), pSong);
		

		return true;
	}

	errorString = "Snotify[AddSong]: Song Already Exists\n";
	return false;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	cHashElement<int, cSong*>* iterator = m_songsList.Find(pSong->getUniqueID());

	if (iterator == nullptr)
	{
		errorString = "Snotify[UpdateSong]: Song doesnt exist\n";
		return false;
	}

	iterator->value = pSong;
	return true;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	cHashElement<int, cSong*>* iterator = m_songsList.Find(UniqueSongID);

	if (iterator == nullptr)
	{
		errorString = "Snotify[Delete] Song Doesn't Exist\n";
		return false;
	}

	cSong* song = iterator->value;
	delete song;
	song = nullptr;
	m_songsList.Remove(UniqueSongID);
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	if (pNewSong == nullptr)
	{
		printf("No valid song \n");
		return false;

	}
	SnotifyUser* user = GetUser(snotifyUserID);

	if (user == nullptr)
	{
		return false;
	}

	std::shared_ptr<UserSongs> song = std::make_shared<UserSongs>();

	song->songID = pNewSong->getUniqueID();
	song->rating = 0;
	song->playbackCount = 0;

	user->songPlayList.Emplace(song);

	return true;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{

	SnotifyUser* user = GetUser(snotifyUserID);

	if (user == nullptr)
	{
		return false;
	}

	bool found = false;

	for (int i = 0; i < user->songPlayList.Size(); i++)
	{
		if (user->songPlayList[i]->songID == SnotifySongID)
		{
			user->songPlayList[i] = user->songPlayList.Back();
			user->songPlayList.Pop();

			found = true;
			break;
		}
	}

	if (!found) { printf("No Song Found with the id , %d\n", SnotifySongID); return false; }

	return true;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	UserSongs* song = GetSongData(SnotifyUserID, songUniqueID);
	
	if(song == nullptr)
	{
		return false;
	}

	song->rating = newRating;


	return true;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	return nullptr;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	UserSongs* song = GetSongData(snotifyUserID, songUniqueID);

	if (song == nullptr)
	{
		return false;
	}

	songRating = song->rating;

	return true;

	

}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	UserSongs* song = GetSongData(snotifyUserID, songUniqueID); 

	if (song == nullptr) 
	{ 
		return false;
	}

	numberOfPlays = song->playbackCount;

	return true;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	cHashElement<int, cPerson*>* iterator = m_userListSIN.Find(SIN);

	if (iterator == nullptr)
	{
		printf("Snotify : Couldn't Find User with SIN :[%d] \n",SIN);
		return nullptr;
	}

	return iterator->value;


}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	cHashElement<int, int>* snotIterator = m_snotifyIDToSIN.Find(SnotifyID);

	if (snotIterator == nullptr)
	{
		printf("Snotify : Couldn't Find User with Snotify ID :[%d] \n", SnotifyID);
		return nullptr;
	}

	cHashElement<int, cPerson*>* iterator = m_userListSIN.Find(snotIterator->value);

	if (iterator == nullptr)
	{
		//printf("Snotify : Couldn't Find User with SIN :[%d] ", SIN);
		return nullptr;
	}

	return iterator->value;
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	return nullptr;
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	cHashElement<int, cSong*>* snotIterator = m_songsList.Find(uniqueID);

	if (snotIterator == nullptr)
	{
		printf("Snotify[FindSong] : Song doesnt exist with id %d ",uniqueID);
		return nullptr;
	}

	cSong* song = snotIterator->value;

	return song;
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

UserSongs* cSnotify::GetSongData(const unsigned int snotifyUserID, const unsigned int snotifySongID)
{
	SnotifyUser* user = GetUser(snotifyUserID);

	if (user == nullptr)
	{
		return nullptr;
	}

	UserSongs* song = nullptr;


	for (int i = 0; i < user->songPlayList.Size(); i++)
	{
		if (user->songPlayList[i]->songID == snotifySongID)
		{
			song = user->songPlayList[i].get();

			break;
		}
	}

	if (song == nullptr)
	{
		printf("No Song Found with the id , %d\n", snotifySongID);
	}

	return song;

}

SnotifyUser* cSnotify::GetUser(const unsigned int snotifyUserID)
{
	SnotifyUser* user = nullptr;

	for (int i = 0; i < m_UserSongDictionary.Size(); i++)
	{
		if (m_UserSongDictionary[i]->userId == snotifyUserID)
		{
			user = m_UserSongDictionary[i].get();
			break;
		}

	}

	if (user == nullptr)
	{
		printf("No User Found with the id , %d\n", snotifyUserID);
	}

	return user;
}

