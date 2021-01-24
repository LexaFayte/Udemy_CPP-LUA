#pragma once
#include <vector>
#include <string>
#include <typeinfo>
#include "Constants.h"

class Component;
class EntityManager;

class UniqueID
{
public:
	unsigned int id;
	UniqueID()
	{
		id = nextID++;
	}

	UniqueID(const UniqueID& orig) : id(orig.id)
	{
		
	}

	UniqueID& operator=(const UniqueID& orig)
	{
		id = orig.id;
		return(*this);
	}

	// Operator overload
	bool operator==(const UniqueID& other)
	{
		return this->id == other.id;
	}

	bool operator!=(const UniqueID& other)
	{
		return !(this->id == other.id);
	}

protected:
	static unsigned int nextID;
};

class Entity
{
	// FUNCTIONS
public:
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name, LayerType layer);
	~Entity() {};


	// TO DO (because they will be stored in vectors, which when they expand their size, perform a copy)
	//move constructor


	// copy constructor
	Entity (const Entity& other);

	// move constructor
	Entity(Entity&& other) noexcept;

	// copy assignment
	Entity& operator=(const Entity& other);

	// move assignment
	Entity& operator=(Entity&& other);


	void Update(float deltaTime);
	void Render();
	void Destroy();

	inline bool IsActive() const noexcept { return _isActive; }

	template<typename T>
	bool HasComponent()
	{
		auto it = std::find_if(_components.begin(), _components.end(), [](auto* arg)
			{
				return typeid(*arg) == typeid(T);
			});

		return it != _components.end();
	}

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args)
	{
		T* comp(new T(std::forward<TArgs>(args)...));
		_components.emplace_back(comp);
		_components.back()->Initialize(this);
		return *comp;
	};

	template<typename T>
	T* GetComponent()
	{
		auto it = std::find_if(_components.begin(), _components.end(), [](auto* arg)
			{
				return typeid(*arg) == typeid(T);
			});

		return static_cast<T*>(*it);
	}

	inline std::vector<Component*>& const GetComponents() noexcept
	{
		return _components;
	}

	// Operator Overload
	bool operator==(const Entity& other)
	{
		return this->_uID == other._uID;
	}

	bool operator!=(const Entity& other)
	{
		return !(this->_uID == other._uID);
	}

private:

	// VARS
public:
	std::string name;
	LayerType layer;

protected:
	EntityManager& _manager;
	std::vector<Component*> _components;
	UniqueID _uID;
	bool _isActive = false;

private:

};