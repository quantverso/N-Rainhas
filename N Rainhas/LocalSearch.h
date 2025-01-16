#ifndef QUANTVERSO_SEARCH_H
#define QUANTVERSO_SEARCH_H

//--------------------------------------------------------------------------------------------------

#include "Board.h"
#include "Random.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------

class LocalSearch
{
public:
	struct Move
	{
		int column, row, attacks;
	};

	LocalSearch(Board& board);

protected:
	Board& board;

	Move GenerateNeighbour();
};

//--------------------------------------------------------------------------------------------------

#endif
