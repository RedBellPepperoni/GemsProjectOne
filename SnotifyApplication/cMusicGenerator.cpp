#include "cMusicGenerator.h"

cMusicGenerator::cMusicGenerator()
{
}

cMusicGenerator::~cMusicGenerator()
{
}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
    return false;
}

cSong* cMusicGenerator::getRandomSong(void)
{
    return nullptr;
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
    return nullptr;
}

bool cMusicGenerator::StoreNewSong(cSong* song)
{
    std::string combinedname = song->artist + "_" +song->name;



    return false;
}
