#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"
#include <cmath>


CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner,
	float radius,
	exVector2 velocity,
	bool isStatic,
	bool isGravityEnabled) :
	PhysicsComponent(owner, velocity, isStatic, isGravityEnabled),
	mRadius(radius)
{

}

bool CircleColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
	if (!otherComponent.expired())
	{
		if (std::shared_ptr<CircleColliderComponent> OtherCircleColliderComponent = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent.lock()))
		{
			exVector2 SelfCenterPos;
			exVector2 OtherCenterPos;

			if (!mOwner.expired())
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
				{
					SelfCenterPos = TransformComp->GetLocation();
				}
			}

			if (!otherComponent.lock()->GetOwner().expired())
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = OtherCircleColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>())
				{
					OtherCenterPos = TransformComp->GetLocation();
				}
			}

			exVector2 Length = SelfCenterPos - OtherCenterPos;
			float DistanceSquared = (Length.x * Length.x) + (Length.y * Length.y);
			float RadiusSum = mRadius + OtherCircleColliderComponent->GetRadius();
			return DistanceSquared < (RadiusSum * RadiusSum);
		}

		if (std::shared_ptr<BoxColliderComponent> OtherBoxColliderComponent = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent.lock()))
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
				if (const std::shared_ptr<TransformComponent> TransformComp = OtherBoxColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>())
				{
					otherCenterPos = TransformComp->GetLocation();
				}
			}

			float rWidth = OtherBoxColliderComponent->GetWidth();
			float rHeight = OtherBoxColliderComponent->GetHeight();
			otherCenterPos.x = otherCenterPos.x - (rWidth / 2);
			otherCenterPos.y = otherCenterPos.y - (rHeight / 2);

			exVector2 testPos = selfCenterPos;

			// Calculates which side of the square the circle is colliding with
			if (selfCenterPos.x < otherCenterPos.x) testPos.x = otherCenterPos.x;
			else if (selfCenterPos.x > (otherCenterPos.x + rWidth)) testPos.x = otherCenterPos.x + rWidth;

			if (selfCenterPos.y < otherCenterPos.y) testPos.y = otherCenterPos.y;
			else if (selfCenterPos.y > (otherCenterPos.y + rHeight)) testPos.y = otherCenterPos.y + rHeight;

			exVector2 length = testPos - selfCenterPos;
			float distanceSquared = ((length.x * length.x) + (length.y * length.y));
			float radius = mRadius * mRadius;
			return (distanceSquared <= radius);
		}
	}
	
	return false;
}

// Resolution for Circle
void CircleColliderComponent::CollisionResolution()
{
	
}

float CircleColliderComponent::GetRadius() const
{
	return mRadius;
}
