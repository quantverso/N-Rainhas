#ifndef QUANTVERSO_TRANSFORM_H
#define QUANTVERSO_TRANSFORM_H

//--------------------------------------------------------------------------------------------------

#include "Component.h"
#include "Rectangle.h"

//--------------------------------------------------------------------------------------------------

class Transform : public Component, public Rectangle
{
public:
	Transform(Entity* entity) :
		Component(entity)
	{
	}

private:
	friend class Entity;
	friend class Component;
};

//--------------------------------------------------------------------------------------------------

#endif
