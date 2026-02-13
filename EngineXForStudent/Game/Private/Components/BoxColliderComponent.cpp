#include "Game/Public/Components/BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity, bool isStatic, bool isGravityEnabled)
	: PhysicsComponent(owner, velocity, isStatic, isGravityEnabled),
	mWidth(width),
	mHeight(height)
{ }

bool BoxColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
	// Checks that other component exists
	if (!otherComponent.expired())
	{
		if (std::shared_ptr )
	}

	return false;
}

