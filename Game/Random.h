#ifndef QUANTVERSO_RANDOM_H
#define QUANTVERSO_RANDOM_H

//--------------------------------------------------------------------------------------------------

#include "Board.h"
#include <random>

//--------------------------------------------------------------------------------------------------

namespace Random
{
	static std::mt19937 mt{ std::random_device{}() };

	int GenerateRow();
	float GenerateReal();
};

//--------------------------------------------------------------------------------------------------

inline int Random::GenerateRow()
{
	static std::uniform_int_distribution rand{ 0, Board::NumberOfQueens - 1 };
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
