#ifndef QUANTVERSO_RANDOM_H
#define QUANTVERSO_RANDOM_H

//--------------------------------------------------------------------------------------------------

#include "NQueens.h"
#include <random>

//--------------------------------------------------------------------------------------------------

class Random
{
	inline static std::random_device rd;

public:
	inline static std::mt19937 mt{ rd() };

	static int GenerateRow();
	static float GenerateReal();
};

//--------------------------------------------------------------------------------------------------

inline int Random::GenerateRow()
{
	static std::uniform_int_distribution rand{ 0, NQueens::N - 1 };
	return rand(mt);
}

//--------------------------------------------------------------------------------------------------

inline float Random::GenerateReal()
{
	static std::uniform_real_distribution<float> rand{ 0, 1 };
	return rand(mt);
}

//--------------------------------------------------------------------------------------------------

#endif
