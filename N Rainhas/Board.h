#ifndef QUANTVERSO_BOARD_H
#define QUANTVERSO_BOARD_H

//--------------------------------------------------------------------------------------------------

#include <array>

//--------------------------------------------------------------------------------------------------

class Board
{
public:
	static constexpr int NumberOfQueens{ 8 };

	struct Queen
	{
		enum Status
		{
			Safe,
			UnderAttack
		};

		int	   row;
		Status status;
	};

	void MoveQueen(int column, int row);
	void Copy(const Board& board, int from, int to);
	void Shuffle();

	int CheckAttacks() const;
	const Queen& GetQueen(int column) const;

private:
	mutable std::array<Queen, NumberOfQueens> queens;
};

//--------------------------------------------------------------------------------------------------

inline void Board::MoveQueen(int column, int row)
{
	queens[column].row = row;
}

//--------------------------------------------------------------------------------------------------

inline void Board::Copy(const Board& board, int from = 0, int to = NumberOfQueens)
{
	std::copy(board.queens.begin() + from, board.queens.begin() + to, this->queens.begin() + from);
}

//--------------------------------------------------------------------------------------------------

inline const Board::Queen& Board::GetQueen(int column) const
{
	return queens[column];
}

//--------------------------------------------------------------------------------------------------

#endif
