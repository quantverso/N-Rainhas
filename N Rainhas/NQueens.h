#ifndef QUANTVERSO_NQUEENS_H
#define QUANTVERSO_NQUEENS_H

//--------------------------------------------------------------------------------------------------

#include "Scene.h"
#include "Queen.h"
#include <array>

//--------------------------------------------------------------------------------------------------

class NQueens : public Scene
{
public:
	static constexpr int N{ 8 };

	NQueens();

	void Start();
	void Update() override;
	void Draw() override;
	void Move(int column, int row);
	void Move(std::array<int, N>& rows);
	void Shuffle();

	int CheckAttacks(const std::array<int, N>& rows) const;
	int CheckAttacks() const;
	const int& GetRow(int column) const;

private:
	Rectangle			  square;
	std::array<Queen*, N> queens;
	std::array<int, N>	  rows;
};

//--------------------------------------------------------------------------------------------------

inline void NQueens::Move(int column, int row)
{
	rows[column] = row;
}

//--------------------------------------------------------------------------------------------------

inline void NQueens::Move(std::array<int, N>& rows)
{
	this->rows = rows;
}

//--------------------------------------------------------------------------------------------------

inline const int& NQueens::GetRow(int column) const
{
	return rows[column];
}

//--------------------------------------------------------------------------------------------------

#endif
