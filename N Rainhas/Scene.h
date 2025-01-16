#ifndef QUANTVERSO_SCENE_H
#define QUANTVERSO_SCENE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Texture.h"
#include "Rectangle.h"
#include "Point.h"
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>

class Entity;

using ObjectsMap = std::unordered_map<std::string, Entity*>;

// ------------------------------------------------------------------------------------------------

class Scene
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Construtor padrão.
	/// 
	////////////////////////////////////////////////////////////
	Scene();

	////////////////////////////////////////////////////////////
	/// \brief Destrutor virtual.
	/// 
	////////////////////////////////////////////////////////////
	virtual ~Scene();

	////////////////////////////////////////////////////////////
	/// \brief Inicializa objetos derivados desta classe.
	/// 
	/// É obrigatório implementá-lo nas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Start() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Atualiza entidades da cena.
	/// 
	/// Chama o método Update() para cada objeto registrado,
	/// atualizando seu estado.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Update();

	////////////////////////////////////////////////////////////
	/// \brief Desenha todo contéudo da cena.
	/// 
	/// Desenha a textura da cena e chama o método Draw()
	/// para cada objeto registrado, desenhando seu conteúdo.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Draw();

	////////////////////////////////////////////////////////////
	/// \brief Instancia um objeto na cena.
	///
	/// Se o ID (único) for informado, o objeto será adicionado
	/// à tabela hash e poderá ser recuperado posteriormente
	/// usando o método FindObject(). O objeto será destruído
	/// automaticamente quando o destrutor da cena for chamado.
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade 
	/// a ser instanciada. Se não fornecida ou não for única,
	/// o objeto não será registrado na tabela hash.
	/// 
	/// \return Um ponteiro para o objeto do tipo `T`.
	///
	////////////////////////////////////////////////////////////
	template <typename T, typename... Args>
	T* CreateObject(const char* id = nullptr, Args&&... args);

	////////////////////////////////////////////////////////////
	/// \brief Adiciona um objeto existente à cena.
	///
	/// Se o ID (único) for informado, o objeto será adicionado
	/// à tabela hash e poderá ser recuperado posteriormente
	/// usando o método FindObject(). O objeto não será destruído
	/// pela cena (precisa ser destruído manualmente).
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade 
	/// a ser instanciada. Se não fornecida ou não for única,
	/// o objeto não será registrado na tabela hash.
	///
	////////////////////////////////////////////////////////////
	void AddObject(Entity* obj, const char* id);

	////////////////////////////////////////////////////////////
	/// \brief Encontra um objeto registrado pelo nome e retorna o tipo específico.
	///
	/// Este método genérico busca um objeto pelo seu id (chave) na
	/// tabela de objetos. Se o objeto for encontrado,
	/// retorna um ponteiro para o tipo derivado.
	///
	/// \tparam T O tipo de entidade esperado.
	/// 
	/// \param id A chave que identifica a entidade a ser buscada.
	/// 
	/// \return Um ponteiro para o tipo `T` se a entidade for encontrada e
	/// corresponder ao tipo; caso contrário, retorna `nullptr`.
	///
	////////////////////////////////////////////////////////////
	template<typename T>
	T* FindObject(const std::string& id);

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de uma textura.
	///
	/// \param texture Referência para o objeto `Texture` que será utilizado
	/// para definir a textura do background.
	///
	///////////////////////////////////////////////////////////
	void SetBackground(const Texture* texture);

protected:
	static Window& window;
	static float&  deltaTime;
	bool		   visible;

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de um arquivo.
	///
	/// Este método carrega uma textura a partir de um arquivo especificado e a 
	/// define para o background.
	///
	/// \param file Caminho para o arquivo de textura que será carregado e 
	/// utilizado para definir a textura do sprite.
	/// 
	///////////////////////////////////////////////////////////
	void SetBackground(const char* file);	

private:
	friend class Component;

	// Variáveis da cena
	std::shared_ptr<Texture>	 texture;	  ///< Textura carregada na cena

	// Variáveis de entidade
	ObjectsMap					 objMap;	  ///< Hash de objetos
	std::list<Entity*>           objects;	  ///< Lista de objetos
	std::list<Entity*>::iterator current;	  ///< Iterador para o objeto atual	
	std::vector<Entity*>         created;	  ///< Vetor de objetos a serem inicializados (próximo frame)
	std::unordered_set<Entity*>  destroyable; ///< Objetos que serão destruídos pela cena
};

// ------------------------------------------------------------------------------------------------

template <typename T, typename... Args>
T* Scene::CreateObject(const char* id, Args&&... args)
{
	T* obj{ new T{ std::forward<Args>(args)... } };
	AddObject(obj, id);
	destroyable.insert(obj);
	return obj;
}

// ------------------------------------------------------------------------------------------------

template<typename T>
T* Scene::FindObject(const std::string& id)
{
	auto it = objMap.find(id);
	if (it != objMap.end())
		return dynamic_cast<T*>(it->second);
	return nullptr;
}

// ------------------------------------------------------------------------------------------------

#endif
