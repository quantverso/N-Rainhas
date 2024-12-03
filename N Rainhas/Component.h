#ifndef QUANTVERSO_COMPONENT_H
#define QUANTVERSO_COMPONENT_H

//--------------------------------------------------------------------------------------------------

#include "Engine.h"

//--------------------------------------------------------------------------------------------------

class Entity;
class Transform;
class Collider;

//--------------------------------------------------------------------------------------------------

class Component
{
public:
	bool visible;

	Component(Entity*& entity);
	virtual ~Component() = default;

protected:
	static Window& window; ///< Referência para a janela gráfica
	Entity* const  entity; ///< Entidade a qual pertence o componente
	Scene* const&  scene;  ///< Referência para a cena
};

//--------------------------------------------------------------------------------------------------

#endif
