#ifndef QUANTVERSO_NQUEENS_H
#define QUANTVERSO_NQUEENS_H

//--------------------------------------------------------------------------------------------------

#include "Scene.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------

class NQueens : public Scene
{
public:
	NQueens();

	void Start();
	void Update() override;
	void Draw() override;

private:
	friend class Queen;

	Board	  board;
	Rectangle square;
};

//--------------------------------------------------------------------------------------------------

#endif
