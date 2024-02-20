#include "cHashMap.h"

unsigned int GenerateHash(const int& key, const unsigned int& cHashMapsize)
{
	return (key * HASH_NUM) % cHashMapsize;
}

unsigned int GenerateHash(const std::string& key, const unsigned int& cHashMapsize)
{
    unsigned int position = 0;
    for (unsigned int i = 0; i < key.size(); i++)
    {
        position += key[i] * i;
    }

    return position % cHashMapsize;
}

unsigned int GenerateHash(const char* key, const unsigned int& cHashMapsize)
{
    unsigned int position = 0;
    for (unsigned int i = 0; key[i] != '\0'; i++)
    {
        position += key[i] * i;
    }

    return position % cHashMapsize;
}
