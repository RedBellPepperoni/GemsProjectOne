#ifndef _cRandom_HG
#define _cRandom_HG


#include <random>

class cRandom
{
private:
	std::mt19937 m_randomGenerator;

public:

	static uint32_t RandomSeed();
	static cRandom Range;


	inline cRandom()
	{

	}

	inline cRandom(uint32_t seed)
		: m_randomGenerator(seed)
		
	{

	}


	inline float operator()(float min, float max)
	{
		
		std::uniform_real_distribution<float> realDist(min, max);
		return realDist(m_randomGenerator);
	}

	inline int32_t operator()(int32_t min, int32_t max)
	{
		
		std::uniform_int_distribution<int32_t> intDist(min, max);
		return intDist(m_randomGenerator);
	}

	inline uint32_t operator()(uint32_t min, uint32_t max)
	{
		
		std::uniform_int_distribution<uint32_t> uintDist(min, max);
		return uintDist(m_randomGenerator);
	}

	// Random gen for float value
	inline float Get(float min, float max)
	{
		
		std::uniform_real_distribution<float> realDist(min, max);
		return realDist(m_randomGenerator);
	}

	// random gen for int 32 values
	inline int32_t Get(int32_t min, int32_t max)
	{
		
		std::uniform_int_distribution<int32_t> intDist(min, max);
		return intDist(m_randomGenerator);
	}

	// random gen for unsigned int 32 values
	inline uint32_t Get(uint32_t min, uint32_t max)
	{
		
		std::uniform_int_distribution<uint32_t> uintDist(min, max);
		return uintDist(m_randomGenerator);
	}

	inline bool GetRandomBool()
	{
		return (bool)Get(0, 1);
	}


};



#endif // !_cRandom_HG

