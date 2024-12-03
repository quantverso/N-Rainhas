#include "Component.h"
#include "Scene.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------

Window& Component::window{ Engine::window }; ///< Referência para a janela gráfica

//--------------------------------------------------------------------------------------------------

Component::Component(Entity*& entity) :
	visible(false),
	entity(entity),
	scene(entity->scene)
{	
}

//--------------------------------------------------------------------------------------------------
