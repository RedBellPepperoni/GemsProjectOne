#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include "cRandom.h"
#include "cSong.h"
#include "cVector.h"

class cMusicGenerator
{
public:
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);
	
	// Returns 0, NULL, or nullptr if no song is found
	// This must be an EXACT MATCH for what's in the billboard100 file. 
	// So case sensitive, etc. 
	cSong* findSong(std::string songName, std::string artist);

private:


	cVector<cSong*> m_songDataBase;

	cVector<int> m_artistDatabase;

};

#endif
