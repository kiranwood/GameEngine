#pragma once
#include "Game/Public/Components/PhysicsComponent.h"

class BoxColliderComponent : public PhysicsComponent
{
	friend class Actor;

public:

	BoxColliderComponent() = delete;

	BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity = { 0.0f, 0.0f },
		bool isStatic = false, bool isGravityEnabled = false);

	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent);
	virtual void CollisionResolution() override;


private:

	float mWidth;
	float mHeight;

};