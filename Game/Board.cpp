#include "Board.h"
#include "Random.h"

//--------------------------------------------------------------------------------------------------

void Board::Shuffle()
{
	for (auto& queen : queens)
		queen.row = Random::GenerateRow();
}

//--------------------------------------------------------------------------------------------------

int Board::CheckAttacks() const
{
	int attacks{};

	for (auto& queen : queens)
		queen.status = Queen::Safe;

	for (int i{}; i < NumberOfQueens - 1; i++)
	{
		for (int j{ i + 1 }; j < NumberOfQueens; j++)
		{
			if (queens[i].row == queens[j].row || abs(queens[i].row - queens[j].row) == abs(i - j))
			{
				attacks++;

				queens[i].status = Queen::UnderAttack;
				queens[j].status = Queen::UnderAttack;
			}
		}
	}

	return attacks;
}

//--------------------------------------------------------------------------------------------------
