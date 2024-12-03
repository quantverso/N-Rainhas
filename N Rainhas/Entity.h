#ifndef QUANTVERSO_ENTITY_H
#define QUANTVERSO_ENTITY_H

//--------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Material.h"
#include "Transform.h"
#include "Texture.h"
#include "Text.h"
#include "Rectangle.h"
#include "Point.h"
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <typeindex>

using ComponentsMap = std::unordered_map<std::type_index, std::unique_ptr<Component>>;

class Scene;

//--------------------------------------------------------------------------------------------------

class Entity
{
public:
    const std::string& id;      ///< Identificação única do objeto
    const std::string& tag;     ///< Tag para agrupar o objeto
    Scene* const&      scene;   ///< Referencia para a cena
    bool               visible; ///< Controla a visibilidade do objeto

    ////////////////////////////////////////////////////////////
    /// \brief Construtor padrão.
    /// 
    ////////////////////////////////////////////////////////////
    Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor virtual.
    /// 
    ////////////////////////////////////////////////////////////
    virtual ~Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Define a tag associada ao objeto.
    ///
    /// A tag é uma string que pode ser usada para agrupar ou identificar
    /// objetos, permitindo a categorização de múltiplos objetos sob a mesma tag.
    /// Ao contrário do ID, que é único para cada objeto,
    /// a mesma tag pode ser compartilhada entre vários objetos.
    ///
    /// \param tag A string contendo a nova tag do objeto. Se for
    /// nullptr ou uma string vazia, a tag do objeto será removida
    /// ou resetada para o valor padrão.
    ///
    ////////////////////////////////////////////////////////////
    void Tag(const char* tag);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um componente à entidade.
    ///
    /// Este método cria e adiciona um novo componente do tipo `T` 
    /// à entidade, passando os argumentos fornecidos para o
    /// construtor do componente. A entidade é associada ao componente.
    ///
    /// \tparam Args Tipos dos argumentos a serem passados para o construtor do componente.
    /// 
    /// \return Um ponteiro para o componente recém-adicionado.
    ///
    ////////////////////////////////////////////////////////////
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    ////////////////////////////////////////////////////////////
    /// \brief Obtém um componente da entidade atual.
    ///
    /// Este método recupera um componente do tipo `T` associado à 
    /// entidade atual.
    ///
    /// \tparam T O tipo de componente a ser obtido.
    /// 
    /// \return Um ponteiro para o componente solicitado.
    ///
    ////////////////////////////////////////////////////////////
    template<typename T>
    T* GetComponent();

protected:
    static Window& window;    ///< Referencia para a janela gráfica.
    static float&  deltaTime; ///< Tempo decorrido entre frames

    ////////////////////////////////////////////////////////////
    /// \brief Desenha objetos derivados desta classe.
    /// 
    /// Método virtual chamado a cada frame para desenhar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Draw();

private:
    friend class Component;
	friend class Scene;

	std::string                   id_;        ///< Nome do objeto na hash
	std::string                   tag_;       ///< Tag para agrupar o objeto
    Scene*                        scene_;     ///< Referencia interna para a cena
    ComponentsMap                 components; ///< Hash de components
	std::list<Entity*>*			  objects;    ///< Guarda objetos do tipo Entity
	std::list<Entity*>::iterator* current;    ///< Iterador para o objeto atual

    ////////////////////////////////////////////////////////////
    /// \brief Inicializa objetos derivados desta classe.
    /// 
    /// Método virtual chamado uma vez no mesmo frame em que o objeto
    /// é instanciado, logo após sua variável `scene` ser inicializada.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Awake() {};

    ////////////////////////////////////////////////////////////
    /// \brief Inicializa objetos derivados desta classe.
    /// 
    /// Método virtual chamado uma vez no próximo frame após a
    /// criação do objeto.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Start() {};

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza objetos derivados desta classe.
    /// 
    /// Método virtual chamado a cada frame para atualizar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Update() {};

public:	
	Material&  material;
    Transform& transform;
};

//--------------------------------------------------------------------------------------------------

inline void Entity::Tag(const char* tag)
{
    tag_ = tag;
}

// ------------------------------------------------------------------------------------------------

inline void Entity::Draw()
{    
    if (material.texture)
        window.Draw(
            material.texture.get(),
            &material,
            &transform,
            0,
            &transform.offset
        );
}

// ------------------------------------------------------------------------------------------------

template<typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    auto component{ std::make_unique<T>(this, std::forward<Args>(args)...) };
    T* componentPtr{ component.get() };
    components[typeid(T)] = std::move(component);
    return componentPtr;
}

// ------------------------------------------------------------------------------------------------

template<typename T>
T* Entity::GetComponent()
{
    auto it{ components.find(std::type_index(typeid(T))) };
    if (it != components.end())
        return static_cast<T*>(it->second.get());
    return nullptr;
}

// ------------------------------------------------------------------------------------------------

#endif
