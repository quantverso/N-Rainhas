#include "Scene.h"
#include "Engine.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------

Window& Scene::window{ Engine::window };
float&  Scene::deltaTime{ Engine::deltaTime };

// ------------------------------------------------------------------------------------------------

Scene::Scene() :
	visible{ true }
{
}

// ------------------------------------------------------------------------------------------------

Scene::~Scene()
{
	std::vector<Entity*> temp{ objects.begin(), objects.end() };
	for (const auto& obj : temp)
	{
		if (destroyable.find(obj) != destroyable.end())
			delete obj;
	}
	objects.clear();
}

// ------------------------------------------------------------------------------------------------

void Scene::AddObject(Entity* obj, const char* id)
{
	obj->scene_ = this;
	obj->objects = &objects;
	obj->current = &current;
	if (id)
	{
		obj->id_ = id;
		objMap[id] = obj;
	}
	created.push_back(obj);
	obj->Awake();
}

// ------------------------------------------------------------------------------------------------

void Scene::Update()
{
	// Inicializa objetos instanciados
	if (!created.empty())
	{
		std::vector<Entity*> temp{ std::move(created) };
		created.clear();
		for (const auto& obj : temp)
		{
			obj->Start();
			objects.push_back(obj);
		}
	}

	// Atualiza objetos
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		current = it;
		(*current)->Update();
	}
}

// ------------------------------------------------------------------------------------------------

void Scene::Draw()
{
	if (texture && visible)
		window.Draw(texture.get());

	// Desenha entidades
	for (const auto& obj : objects)
	{
		if (obj->visible)
			obj->Draw();
	}
}

// ------------------------------------------------------------------------------------------------

void Scene::SetBackground(const Texture* texture)
{
	this->texture = std::shared_ptr<Texture>(const_cast<Texture*>(texture), [](Texture*) {});
}

// ------------------------------------------------------------------------------------------------

void Scene::SetBackground(const char* file)
{
	texture = std::make_unique<Texture>();
	texture->Load(file);
}

// ------------------------------------------------------------------------------------------------
