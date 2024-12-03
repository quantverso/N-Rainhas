#ifndef QUANTVERSO_HILLCLIMBING_H
#define QUANTVERSO_HILLCLIMBING_H

//--------------------------------------------------------------------------------------------------

#include "LocalSearch.h"
#include "NQueens.h"

//--------------------------------------------------------------------------------------------------

class HillClimbing : public LocalSearch
{
public:
	HillClimbing(NQueens* queens);

private:
	Move Heuristic();
};

//--------------------------------------------------------------------------------------------------

#endif
