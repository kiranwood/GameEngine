#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"

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
		if (std::shared_ptr<CircleColliderComponent> OtherCircleColliderComponent = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent.lock()))
		{
			exVector2 selfCenterPos;
			exVector2 otherCenterPos;

			if (!mOwner.expired())
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
				{
					selfCenterPos = TransformComp->GetLocation();
				}
			}

			if (!otherComponent.lock()->GetOwner().expired())
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = OtherCircleColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>())
				{
					otherCenterPos = TransformComp->GetLocation();
				}
			}

			exVector2 testPos = otherCenterPos;
			selfCenterPos.x = otherCenterPos.x - (mWidth / 2);
			selfCenterPos.y = otherCenterPos.y - (mHeight / 2);

			// Calculates which side of the square the circle is colliding with
			if (otherCenterPos.x < selfCenterPos.x) testPos.x = selfCenterPos.x;
			else if (otherCenterPos.x > (selfCenterPos.x + mWidth)) testPos.x = selfCenterPos.x + mWidth;

			if (otherCenterPos.y < selfCenterPos.y) testPos.y = selfCenterPos.y;
			else if (otherCenterPos.y > (selfCenterPos.y + mHeight)) testPos.y = selfCenterPos.y + mHeight;

			exVector2 length = otherCenterPos - testPos;
			float distanceSquared = (length.x * length.x) + (length.y * length.y);
			float radiusSum = OtherCircleColliderComponent->GetRadius() * OtherCircleColliderComponent->GetRadius();
			return (distanceSquared < radiusSum);
		}
	}

	return false;
}

void BoxColliderComponent::CollisionResolution()
{

}

float BoxColliderComponent::GetWidth()
{
	return mWidth;
}

float BoxColliderComponent::GetHeight()
{
	return mHeight;
}

