#include "Entity.h"
#include "Engine.h"
#include "Scene.h"

// ------------------------------------------------------------------------------------------------

Window&	Entity::window{ Engine::window };
float&	Entity::deltaTime{ Engine::deltaTime };

//--------------------------------------------------------------------------------------------------

Entity::Entity() :	
	id{ id_ },
	tag{tag_},
	scene{ scene_ },
	visible{ true },
	scene_{},
	material{ *AddComponent<Material>() },
	transform{ *AddComponent<Transform>() }
{
}

// ------------------------------------------------------------------------------------------------

Entity::~Entity()
{
	if (current && this == *(*current))
		objects->erase(*current);
	else if (objects)
		objects->remove(this);
}

// ------------------------------------------------------------------------------------------------
