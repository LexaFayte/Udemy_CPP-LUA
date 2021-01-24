#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <functional>
#include "Constants.h"

class Entity;

// ======================================================================================================
// #COLLISION_DATA_STRCUTURES
// ======================================================================================================

enum class CollisionLayer
{
	NONE = 0,
	PLAYER,
	ENEMY,
	PROJECTILE,
	ENVIRONMENT,
	LEVEL_TRIGGER,

	COLLISION_LAYER_COUNT
};

struct CollisionData
{
public:
	bool isColliding = false;
	CollisionType entityCollisionTypeA = CollisionType::NONE;
	CollisionType entityCollisionTypeB = CollisionType::NONE;
	CollisionType collisionTypeResult = CollisionType::NONE;
};

struct CollisionParameters
{
	// FUNCTIONS
public:

	void changeCollisionLayerFlag(CollisionLayer layer, bool useLayer)
	{
		_collisionLayerSettings[layer] = useLayer;
	}

	bool getCollisionLayerFlag(CollisionLayer layerType)
	{
		return _collisionLayerSettings[layerType];
	}

	// VARS
public:
	CollisionLayer entityLayer = CollisionLayer::NONE;

private:
	std::map<CollisionLayer, bool> _collisionLayerSettings
	{
		std::pair<CollisionLayer, bool>(CollisionLayer::PLAYER, true),
		std::pair<CollisionLayer, bool>(CollisionLayer::ENEMY, true),
		std::pair<CollisionLayer, bool>(CollisionLayer::PROJECTILE, true),
		std::pair<CollisionLayer, bool>(CollisionLayer::ENVIRONMENT, true),
		std::pair<CollisionLayer, bool>(CollisionLayer::LEVEL_TRIGGER, false)
	};
	

};

// ======================================================================================================
// #COLLISION_CALLBACKS
// ======================================================================================================

//struct CallBackFunction
//{
//
//private:
//	int mTicket = 0;
//public:
//	std::function<void()> mFunction;
//
//	CallBackFunction() {};
//
//	CallBackFunction(std::function<void()>& fn, int ticket)
//	{
//		mFunction = fn;
//		mTicket = ticket;
//	}
//
//	bool operator==(CallBackFunction& rhs)
//	{
//		if (mTicket == rhs.mTicket)
//		{
//			return true;
//		}
//		return false;
//	}
//};
//
//namespace _CollisionCallBack
//{
//	struct CallBack
//	{
//	private:
//		std::vector<CallBackFunction> mRegisteredFunctions;
//	public:
//		void operator+=(CallBackFunction rhs)
//		{
//			mRegisteredFunctions.push_back(rhs);
//		}
//
//		void operator-=(CallBackFunction rhs)
//		{
//			for (auto it = mRegisteredFunctions.begin(); it != mRegisteredFunctions.end(); ++it)
//			{
//				if (*it == rhs)
//				{
//					mRegisteredFunctions.erase(it);
//					break;
//				}
//			}
//		}
//
//		void Execute()
//		{
//			InternalExecute(*this);
//		}
//		
//	private:
//		void InternalExecute(CallBack c)
//		{
//			for (auto& function : c.mRegisteredFunctions)
//			{
//				function.mFunction();
//			}
//		}
//	};
//}

// ======================================================================================================
// #COLLISION_CLASS
// ======================================================================================================

class Collision
{
	// FUNCTIONS
public:
	static void CheckAABBCollisions(const SDL_Rect& rectA, const SDL_Rect& rectB, CollisionData& collisionData);
	static bool InternalCheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);

private:

	// VARS
public:


private:
};