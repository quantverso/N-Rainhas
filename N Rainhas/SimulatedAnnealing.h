#ifndef QUANTVERSO_SIMULATEDANNEALING_H
#define QUANTVERSO_SIMULATEDANNEALING_H

//--------------------------------------------------------------------------------------------------

#include "LocalSearch.h"
#include "NQueens.h"

//--------------------------------------------------------------------------------------------------

class SimulatedAnnealing : public LocalSearch
{
public:
	SimulatedAnnealing(NQueens* queens, int iterations);
};

//--------------------------------------------------------------------------------------------------

#endif
