#pragma once
#include <string>
#include <vector>

class PureEntity;
class PureComponent;
class PureSystem;

/*
* a world (when entity live); could be analogous to a Layer? TBD/WIP
* Base class
* Should hold all components and entities (still TBD as to how)
*/
class World
{
public:
	World() = default;
	~World() {};

	void Update(float deltaTime) {}; // will we need this?

	PureEntity* CreatePureEntity();

private:


public:
	std::string worldName;

private:
	std::vector<PureEntity*> _PureEntities;
};