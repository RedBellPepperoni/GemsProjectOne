#ifndef _cVector_HG
#define _cVector_HG


#include "cAssert.h"
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
// Cutom Vector class trying to mimic stl vector



template <class T> 
class cVector
{
public:
	// Default constructor 
	cVector()
	{
	}

	cVector(const cVector<T>& othercVector);

	// constructor based on capacity and a default value
	cVector(size_t size,T initial = T{}); 
	cVector(cVector<T>&& othercVector) noexcept;

	//Default Destrcutor
	~cVector()
	{
		// Delete all the data pointer refs
		delete[] m_data;
		
	}

	// copy assignment
	cVector<T>& operator=(const cVector<T>&); 

	size_t Size() const { return m_currentIndex; }

	size_t Capacity() const { return m_size; }

	T& Emplace(const T& element);
	T& Emplace(T&& element);

	// Constructs a new Type using the given arguments at the back of the cVector
	template <typename... Args>
	T& EmplaceBack(Args&&... args);

	// Constructs a new Type using the "Default" arguments at the back of the cVector
	T& EmplaceBack();

	T& Back();
	void Pop();
	void Clear(bool deleteData = false);

	bool Empty() const { return m_currentIndex == 0; }

	bool operator==(const cVector<T>& other) const;
	bool operator!=(const cVector<T>& other) const;


	// Custom Iterator to go through the cVector class
	class Iterator
	{
	public:
		Iterator(T* ptr)
			: ptr(ptr)
		{
		}
		Iterator operator++()
		{
			++ptr;
			return *this;
		}
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
		T& operator*() const { return *ptr; }
		Iterator operator+(int offset) const { return Iterator(ptr + offset); }

	private:
		T* ptr;
	};

	Iterator begin() const { return Iterator(m_data); }
	Iterator end() const { return Iterator(m_data + m_currentIndex); }

	T& operator[](const size_t index);
	const T& operator[](const size_t index) const;
	T* Data() { return m_data; }

	void Reserve(const size_t size);

private:

	// The actual pointer to the start of the aligned data
	T* m_data = nullptr;

	// the total size in bytes occupied in memory by this cVector
	size_t m_size = 0;

	// count of the elements stores (basically the total memory used / sizeof(T))
	size_t m_currentIndex = 0;

};

// =========== IMPLEMENTAION OF FUNCTIONS ==============

template<class T>
inline cVector<T>::cVector(const cVector<T>& othercVector)
{

	// Delete before copying everything from another cVector
	delete[] m_data;


	// Copy everything from another cVector
	m_currentIndex = othercVector.Size();
	m_size = othercVector.Capacity();
	m_data = new T[m_size];

	// Iterate through all the elements and copy them over
	for (size_t i = 0; i < m_currentIndex; ++i)
	{
		m_data[i] = othercVector[i];
	}
}

template<class T>
inline cVector<T>::cVector(size_t size, T initial)
	: m_size(size)
	, m_currentIndex(size)
{
	m_data = new T[size];

	// Initlizae each element
	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] = initial;
	}
}

template<class T>
inline cVector<T>::cVector(cVector<T>&& othercVector) noexcept
	: m_data(othercVector.m_data)
	, m_size(othercVector.m_size)
	, m_currentIndex(othercVector.m_currentIndex)
{
}

template<class T>
inline cVector<T>& cVector<T>::operator=(const cVector<T>& othercVector)
{
	// Delete before copying everything from another cVector
	delete[] m_data;

	// Copy everything from another cVector
	m_currentIndex = othercVector.Size();
	m_size = othercVector.Capacity();
	m_data = new T[m_size];

	// Iterate through all the elements and copy them over
	for (size_t i = 0; i < m_currentIndex; ++i)
	{
		m_data[i] = othercVector[i];
	}
	return *this;
}

template<class T>
inline T& cVector<T>::Emplace(const T& element)
{
	// If over cacacity, increase the capacity
	if (m_currentIndex == m_size)
	{
		// handing initial when
		if (m_size == 0)
		{
			Reserve(4);
		}
		else
		{
			// Double the size whenever it goes over
			Reserve(m_size * 2);
		}
	}

	// Append an element to the array
	m_data[m_currentIndex] = element;
	m_currentIndex++;

	return m_data[m_currentIndex - 1];
}

template<class T>
inline T& cVector<T>::Emplace(T&& element)
{
	// If over cacacity, increase the capacity
	if (m_currentIndex == m_size)
	{
		if (m_size == 0)
		{
			Reserve(4);
		}
		else
		{
			// Double the size whenever it goes over
			Reserve(m_size * 2);
		}
	}

	// Append an element to the array
	m_data[m_currentIndex] = std::move(element);
	m_currentIndex++;

	return m_data[m_currentIndex - 1];
}

template<class T>
template<typename ...Args>
inline T& cVector<T>::EmplaceBack(Args && ...args)
{
	// If over cacacity, increase the capacity
	if (m_currentIndex == m_size)
	{
		if (m_size == 0)
		{
			Reserve(4);
		}
		else
		{
			// Double the size whenever it goes over
			Reserve(m_size * 2);
		}
	}

	// Append an element to the array
	m_data[m_currentIndex] = T(std::forward<Args>(args)...);
	m_currentIndex++;

	return m_data[m_currentIndex - 1];
}


template<class T>
inline T& cVector<T>::EmplaceBack()
{
	// If over cacacity, increase the capacity
	if (m_currentIndex == m_size)
	{
		if (m_size == 0)
		{
			Reserve(4);
		}
		else
		{
			// Double the size whenever it goes over
			Reserve(m_size * 2);
		}
	}

	m_data[m_currentIndex] = T();
	m_currentIndex++;


	return m_data[m_currentIndex - 1];
}



template<class T>
inline T& cVector<T>::operator[](const size_t index)
{
	Snp_ASSERT(index < m_currentIndex, "cVector : Index out of bounds");

	return m_data[index];
}

template<class T>
inline const T& cVector<T>::operator[](const size_t index) const
{
	Snp_ASSERT(index < m_currentIndex, "cVector : Index out of bounds");

	return m_data[index];
}

template<class T>
inline void cVector<T>::Reserve(const size_t size)
{
	if (size > m_currentIndex)
	{
		T* temp = new T[size];

		for (size_t i = 0; i < m_size; ++i)
		{
			temp[i] = std::move(m_data[i]);
		}
		delete[] m_data;

		m_size = size;
		m_data = temp;
	}
}

template<class T>
inline T& cVector<T>::Back()
{
	return m_data[m_currentIndex - 1];
}

template<class T>
inline void cVector<T>::Pop()
{
	if (m_currentIndex > 0)
	{
		m_currentIndex--;
	}

	else
	{
		Snp_ASSERT(false, "cVector : No Element to Pop");
	}
}

template<class T>
inline void cVector<T>::Clear(bool deleteData)
{
	if (deleteData)
	{
		delete[] m_data;
		m_currentIndex = 0;
		m_size = 0;
	}
	else
	{
		m_currentIndex = 0;
	}
}



#endif // !_ccVector_HG

