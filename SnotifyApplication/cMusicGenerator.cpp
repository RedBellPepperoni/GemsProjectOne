#include "cMusicGenerator.h"
#include "cFile.h"
#include <fstream>
#include <sstream>

cMusicGenerator::cMusicGenerator()
{
}

cMusicGenerator::~cMusicGenerator()
{
}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	if (!cFile::FileExists(musicFileName))
	{
		errorString = "Music Generator : Couldn't load Billboard List : [File not found]";
		return false;
	}


	std::ifstream namesFile(musicFileName);
	std::string theLine;

	unsigned int lineCount = 0;
	unsigned int loadCount = 0;
	unsigned int duplicateCount = 0;

	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;

		std::string songName;
		std::string artistName;
		
		//Ig nore first line since its just labels
		if (lineCount == 1)
		{
			continue;
		}


		while (std::getline(ssLine, token, ','))
		{

			switch (tokenCount)
			{
				// The Song name
			case 3: songName = token;
				break;

			case 4: // Name of the singer/artist
					artistName = token;
				break;


			}



			tokenCount++;
		}

		// Try to store a new Song
		StoreNewSong(songName, artistName);
	

	}

	return true;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	int randomSongIndex = cRandom::Range((uint32_t)0, (uint32_t)(m_SongDataBase.Entries() - 1));

	cHashElement<int, cSong*>* itr = m_SongDataBase.Find(randomSongIndex);

	if (itr == nullptr)
	{
		return getRandomSong();
	}

    return itr->value;
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
    return nullptr;
}

void cMusicGenerator::LoadMusicDataBase()
{
	std::string errorString;

	if (LoadMusicInformation(musicFilePath, errorString))
	{
		printf("\n----------------------------------------------------\n");
	}

	else
	{
		printf(errorString.c_str());
	}
}

bool cMusicGenerator::StoreNewSong(const std::string& songName, const std::string& artistName)
{
	std::string uniqueKey = songName + artistName; 
	int songId = GenerateHash(uniqueKey, m_SongDataBase.Size());
	// Checking if a entry exists for the given HAsh
	cHashElement<int, cSong*>* duplicateEntry = m_SongDataBase.Find(songId);

	if (duplicateEntry == nullptr)
	{
		// No Entry Found : Create a new Song on the Heap
		cSong* newSong = new cSong();

		newSong->artist = artistName;
		newSong->name = songName;
		
		newSong->SetUniqueID(songId);

		m_SongDataBase.Add(songId, newSong);

		

		
		return true;
	}

	

	return false;


}
