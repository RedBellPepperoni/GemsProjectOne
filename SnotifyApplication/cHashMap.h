#ifndef _cHashMap_HG
#define _cHashMap_HG

#include <stdio.h>
#include <stdlib.h>
#include <string>

 

namespace customHash {

    const unsigned int HASH_NUM = 31337;
    // Size of linked elemnts
    const unsigned int DEFAULTsize = 4;

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

}


template <typename Key, typename Value>
class cHashElement 
{
    bool filled;

public:
    Key key;
    Value value;

    cHashElement();
    explicit cHashElement(const Key& key, const Value& value);
    inline bool IsFilled() const;
};

template <typename Key, typename Value>
cHashElement<Key, Value>::cHashElement() 
    : filled(false) 
{}

template <typename Key, typename Value>
cHashElement<Key, Value>::cHashElement(const Key& key, const Value& value) 
    : key(key), value(value), filled(true) 
{}

template <typename Key, typename Value>
bool cHashElement<Key, Value>::IsFilled() const 
{
    return filled;
}




template <typename Key, typename Value>
class cHashMap 
{

private:
    // Array of linked hashElements
    cHashElement<Key, Value>* hash_entries;
    unsigned int cHashMapsize;
    unsigned int num_entries;

    void Rehash(unsigned int);

public:
    typedef const cHashElement<Key, Value>* const_iterator;
    typedef cHashElement<Key, Value>* iterator;

    cHashMap();
    explicit cHashMap(unsigned int size);
    cHashMap(const cHashMap<Key, Value>& otherMap);
    ~cHashMap();
    inline iterator Begin();
    inline iterator End();
    inline const_iterator cBegin() const;
    inline const_iterator cEnd() const;
    inline unsigned int Size() const;
    inline unsigned int Entries() const;
    const_iterator FindInternalConst(const_iterator& begin, const_iterator& end, const Key& key) const;
    const_iterator Find(const Key& key) const;
    iterator FindInternal(iterator& begin, iterator& end, const Key key);
    iterator Find(const Key& key);
    void Add(const Key& key, const Value& value);
    void Remove(const Key& key);
    Value& operator[](const Key& key);

};



#endif // !_cHashMap_HG
template <typename Key, typename Value>
cHashMap<Key, Value>::cHashMap()
    : hash_entries(new cHashElement<Key, Value>[customHash::DEFAULTsize])
    , cHashMapsize(customHash::DEFAULTsize)
    , num_entries(0)
{
}

template <typename Key, typename Value>
cHashMap<Key, Value>::cHashMap(unsigned int size)
    : hash_entries(new cHashElement<Key, Value>[size])
    , cHashMapsize(size)
    , num_entries(0)
{}

template <typename Key, typename Value>
cHashMap<Key, Value>::cHashMap(const cHashMap<Key, Value>& otherMap)
    : cHashMapsize(otherMap.Size())
    , hash_entries(new cHashElement<Key, Value>[otherMap.Size()])
    , num_entries(0)
{
    for (cHashMap<Key, Value>::const_iterator entry = otherMap.cBegin(); entry != otherMap.cEnd(); entry++)
    {
        if (entry->IsFilled())
        {
            Add(entry->key, entry->value);
        }
    }
}

template <typename Key, typename Value>
cHashMap<Key, Value>::~cHashMap()
{
    delete[] hash_entries;
}

template <typename Key, typename Value>
typename cHashMap<Key, Value>::const_iterator cHashMap<Key, Value>::cBegin() const
{
    return hash_entries;
}

template <typename Key, typename Value>
typename cHashMap<Key, Value>::const_iterator cHashMap<Key, Value>::cEnd() const
{
    return hash_entries + cHashMapsize;
}

template <typename Key, typename Value>
typename cHashMap<Key, Value>::iterator cHashMap<Key, Value>::Begin()
{
    return hash_entries;
}

template <typename Key, typename Value>
typename cHashMap<Key, Value>::iterator cHashMap<Key, Value>::End()
{
    return hash_entries + cHashMapsize;
}

template <typename Key, typename Value>
unsigned int cHashMap<Key, Value>::Size() const
{
    return cHashMapsize;
}

template <typename Key, typename Value>
unsigned int cHashMap<Key, Value>::Entries() const
{
    return num_entries;
}

template <typename Key, typename Value>
typename cHashMap<Key, Value>::const_iterator cHashMap<Key, Value>::FindInternalConst(const_iterator& begin, const_iterator& end, const Key& key) const
{
    for (const_iterator beg = begin; beg != end; ++beg) 
    {
        if (beg->key == key)
        {
            return beg;
        }
    }
    return nullptr;
}




template <typename Key, typename Value>
typename cHashMap<Key, Value>::iterator cHashMap<Key, Value>::FindInternal(iterator& begin, iterator& end, const Key key)
{
    for (iterator beg = begin; beg != end; ++beg)
    {
        if (beg->key == key)
        {
            return beg;
        }
    }
    return nullptr;
}


template<typename Key, typename Value>
typename cHashMap<Key, Value>::const_iterator cHashMap<Key, Value>::Find(const Key& key) const
{
  
    const_iterator find = this->FindInternalConst(cBegin(), cEnd(), key);
    return nullptr;
}


template<typename Key, typename Value>
typename cHashMap<Key, Value>::iterator cHashMap<Key, Value>::Find(const Key& key)
{ 
    iterator end = hash_entries + cHashMapsize;

    cHashMap<Key, Value>::iterator find = this->FindInternal(hash_entries, end, key);
    return find;
}




template <typename Key, typename Value>
void cHashMap<Key, Value>::Rehash(unsigned int newsize)
{
    cHashElement<Key, Value>* new_cHashMap = new cHashElement<Key, Value>[newsize];

    unsigned int old_cHashMapsize = cHashMapsize;
    cHashMapsize = newsize;
    num_entries = 0;

    for (unsigned int i = 0; i < old_cHashMapsize; ++i)
    {
        if (hash_entries[i].IsFilled())
        {
            unsigned int position = customHash::GenerateHash(hash_entries[i].key, cHashMapsize);
            while (new_cHashMap[position].IsFilled())
            {
                position = (position + 1) % cHashMapsize;
            }
            new_cHashMap[position] = cHashElement<Key, Value>(hash_entries[i].key, hash_entries[i].value);
            num_entries += 1;
        }
    }

    delete[] hash_entries;
    hash_entries = new_cHashMap;
}

template <typename Key, typename Value>
void cHashMap<Key, Value>::Add(const Key& key, const Value& value)
{
    if (num_entries >= cHashMapsize)
    {
        Rehash(cHashMapsize * 2);
    }
    unsigned int position = customHash::GenerateHash(key, cHashMapsize);
    while (hash_entries[position].IsFilled())
    {
        position = (position + 1) % cHashMapsize;
    }
    hash_entries[position] = cHashElement<Key, Value>(key, value);
    num_entries += 1;
}


template <typename Key, typename Value>
void cHashMap<Key, Value>::Remove(const Key& key)
{
    unsigned int position = customHash::GenerateHash(key, cHashMapsize);
    for (unsigned int i = 0; i < cHashMapsize; ++i)
    {
        position = (position + 1) % cHashMapsize;
        if (hash_entries[position].key == key) {
            hash_entries[position] = cHashElement<Key, Value>();
            num_entries--;
            return;
        }
    }

    printf("HashMap : key not in HashMap");
}

template <typename Key, typename Value>
Value& cHashMap<Key, Value>::operator[](const Key& key)
{
    unsigned int position = customHash::GenerateHash(key, cHashMapsize);
    unsigned int original_position(position);

    for (unsigned int i = 0; i < cHashMapsize; ++i)
    {
        position = (position + 1) % cHashMapsize;
        if (hash_entries[position].key == key)
        {
            return hash_entries[position].value;
        }
    }

    if (num_entries >= cHashMapsize)
    {
        Rehash(cHashMapsize * 2);
    }

    while (hash_entries[original_position].IsFilled())
    {
        original_position = (original_position + 1) % cHashMapsize;
    }

    hash_entries[original_position] = cHashElement<Key, Value>(key, Value());
    ++num_entries;
    return hash_entries[original_position].value;
}


