#ifndef QUANTVERSO_QUEEN_H
#define QUANTVERSO_QUEEN_H

//--------------------------------------------------------------------------------------------------

#include "Entity.h"

//--------------------------------------------------------------------------------------------------

class Queen : public Entity
{
public:
	Queen();

	void Update();
	void Draw();
	void Align();

private:
	const int column;
	Vector2f  offset;
	bool	  collision;
};

//--------------------------------------------------------------------------------------------------

inline void Queen::Draw()
{
	Align();
	Entity::Draw();
}

//--------------------------------------------------------------------------------------------------

#endif
