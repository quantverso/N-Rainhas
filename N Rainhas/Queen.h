#ifndef QUANTVERSO_QUEEN_H
#define QUANTVERSO_QUEEN_H

//--------------------------------------------------------------------------------------------------

#include "Entity.h"

//--------------------------------------------------------------------------------------------------

class Queen : public Entity
{
public:
	enum AttackStatus
	{
		Safe,
		UnderAttack
	};

	Queen(int column, int& row);

	void Update();
	void Draw();
	void Align();
	void SetAttackStatus(AttackStatus status);

	bool GetAttackStatus() const;

private:
	const int column;
	int&	  row;
	Vector2f  offset;
	bool	  collision;
	bool	  attackStatus;
};

//--------------------------------------------------------------------------------------------------

inline void Queen::Draw()
{
	Align();
	Entity::Draw();
}

//--------------------------------------------------------------------------------------------------

inline void Queen::Align()
{
	if (!Mouse::ButtonPressed(Mouse::Left))
		transform.Position(transform.Size().width * column, transform.Size().height * row);
}

//--------------------------------------------------------------------------------------------------

inline void Queen::SetAttackStatus(AttackStatus status)
{
	attackStatus = bool(status);
}

//--------------------------------------------------------------------------------------------------

inline bool Queen::GetAttackStatus() const
{
	return attackStatus;
}

//--------------------------------------------------------------------------------------------------

#endif
