#ifndef QUANTVERSO_HILLCLIMBING_H
#define QUANTVERSO_HILLCLIMBING_H

//--------------------------------------------------------------------------------------------------

#include "LocalSearch.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------

class HillClimbing : public LocalSearch
{
public:
	HillClimbing(Board& board);

private:
	Move Heuristic();
};

//--------------------------------------------------------------------------------------------------

#endif
