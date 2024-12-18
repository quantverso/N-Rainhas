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
	/// \brief Construtor padr�o.
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
	/// � obrigat�rio implement�-lo nas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Start() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Atualiza entidades da cena.
	/// 
	/// Chama o m�todo Update() para cada objeto registrado,
	/// atualizando seu estado.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Update();

	////////////////////////////////////////////////////////////
	/// \brief Desenha todo cont�udo da cena.
	/// 
	/// Desenha a textura da cena e chama o m�todo Draw()
	/// para cada objeto registrado, desenhando seu conte�do.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Draw();

	////////////////////////////////////////////////////////////
	/// \brief Instancia um objeto na cena.
	///
	/// Se o ID (�nico) for informado, o objeto ser� adicionado
	/// � tabela hash e poder� ser recuperado posteriormente
	/// usando o m�todo FindObject(). O objeto ser� destru�do
	/// automaticamente quando o destrutor da cena for chamado.
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade 
	/// a ser instanciada. Se n�o fornecida ou n�o for �nica,
	/// o objeto n�o ser� registrado na tabela hash.
	/// 
	/// \return Um ponteiro para o objeto do tipo `T`.
	///
	////////////////////////////////////////////////////////////
	template <typename T, typename... Args>
	T* CreateObject(const char* id = nullptr, Args&&... args);

	////////////////////////////////////////////////////////////
	/// \brief Adiciona um objeto existente � cena.
	///
	/// Se o ID (�nico) for informado, o objeto ser� adicionado
	/// � tabela hash e poder� ser recuperado posteriormente
	/// usando o m�todo FindObject(). O objeto n�o ser� destru�do
	/// pela cena (precisa ser destru�do manualmente).
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade 
	/// a ser instanciada. Se n�o fornecida ou n�o for �nica,
	/// o objeto n�o ser� registrado na tabela hash.
	///
	////////////////////////////////////////////////////////////
	void AddObject(Entity* obj, const char* id);

	////////////////////////////////////////////////////////////
	/// \brief Encontra um objeto registrado pelo nome e retorna o tipo espec�fico.
	///
	/// Este m�todo gen�rico busca um objeto pelo seu id (chave) na
	/// tabela de objetos. Se o objeto for encontrado,
	/// retorna um ponteiro para o tipo derivado.
	///
	/// \tparam T O tipo de entidade esperado.
	/// 
	/// \param id A chave que identifica a entidade a ser buscada.
	/// 
	/// \return Um ponteiro para o tipo `T` se a entidade for encontrada e
	/// corresponder ao tipo; caso contr�rio, retorna `nullptr`.
	///
	////////////////////////////////////////////////////////////
	template<typename T>
	T* FindObject(const std::string& id);

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de uma textura.
	///
	/// \param texture Refer�ncia para o objeto `Texture` que ser� utilizado
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
	/// Este m�todo carrega uma textura a partir de um arquivo especificado e a 
	/// define para o background.
	///
	/// \param file Caminho para o arquivo de textura que ser� carregado e 
	/// utilizado para definir a textura do sprite.
	/// 
	///////////////////////////////////////////////////////////
	void SetBackground(const char* file);	

private:
	friend class Component;

	// Vari�veis da cena
	std::shared_ptr<Texture>	 texture;	  ///< Textura carregada na cena

	// Vari�veis de entidade
	ObjectsMap					 objMap;	  ///< Hash de objetos
	std::list<Entity*>           objects;	  ///< Lista de objetos
	std::list<Entity*>::iterator current;	  ///< Iterador para o objeto atual	
	std::vector<Entity*>         created;	  ///< Vetor de objetos a serem inicializados (pr�ximo frame)
	std::unordered_set<Entity*>  destroyable; ///< Objetos que ser�o destru�dos pela cena
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
