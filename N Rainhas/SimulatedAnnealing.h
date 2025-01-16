#ifndef QUANTVERSO_SIMULATEDANNEALING_H
#define QUANTVERSO_SIMULATEDANNEALING_H

//--------------------------------------------------------------------------------------------------

#include "LocalSearch.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------

struct SimulatedAnnealing : public LocalSearch
{
	SimulatedAnnealing(Board& board, int iterations);
};

//--------------------------------------------------------------------------------------------------

#endif
