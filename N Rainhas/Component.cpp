#include "Component.h"
#include "Scene.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------

Window& Component::window{ Engine::window }; ///< Refer�ncia para a janela gr�fica

//--------------------------------------------------------------------------------------------------

Component::Component(Entity*& entity) :
	visible{},
	entity{ entity },
	scene{ entity->scene }
{	
}

//--------------------------------------------------------------------------------------------------
