#ifndef QUANTVERSO_SEARCH_H
#define QUANTVERSO_SEARCH_H

//--------------------------------------------------------------------------------------------------

#include "NQueens.h"
#include "Random.h"

//--------------------------------------------------------------------------------------------------

class LocalSearch
{
public:
	struct Move
	{
		int column, row, attacks;
	};

	LocalSearch(NQueens* queens);

protected:
	NQueens* const queens;

	Move GenerateNeighbour();
};

//--------------------------------------------------------------------------------------------------

#endif
