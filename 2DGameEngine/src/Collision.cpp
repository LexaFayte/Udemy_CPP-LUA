#include "Collision.h"
#include "Entity.h"
#include "Components/ColliderComponent.h"

bool Collision::InternalCheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	return (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y);
}

void Collision::CheckAABBCollisions(const SDL_Rect& rectA, const SDL_Rect& rectB, CollisionData& collisionData)
{
	//#TODO_REFACTOR: we should be returning a list of collisions that happen
	collisionData.isColliding = InternalCheckAABBCollision(rectA, rectB);
	collisionData.collisionTypeResult = collisionData.entityCollisionTypeB;
}