#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineInterface.h"

std::unique_ptr<PhysicsEngine> PhysicsEngine::sPhysicsEngine = nullptr;

PhysicsEngine::~PhysicsEngine()
{
	ClearInvalidPhysicsComponents();
}

void PhysicsEngine::AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd)
{
	mPhysicsComponents.emplace_back(componentToAdd);
}

void PhysicsEngine::ClearInvalidPhysicsComponents()
{
	if (mPhysicsComponents.empty())
	{
		return;
	}

	mPhysicsComponents.remove_if(
		[](const std::weak_ptr<PhysicsComponent>& component)
		{
			return component.expired();
		});
}

void PhysicsEngine::PhysicsUpdate(const float DeltaTime)
{
	ClearInvalidPhysicsComponents();

	for (size_t index1 = 0; index1 < mPhysicsComponents.size(); ++index1)
	{
		std::list<std::weak_ptr<PhysicsComponent>>::iterator firstPhysicsComponentIt = mPhysicsComponents.begin();
		std::advance(firstPhysicsComponentIt, index1);

		if (!firstPhysicsComponentIt->expired())
		{
			std::shared_ptr<PhysicsComponent> firstPhysicsComponentToCheck = firstPhysicsComponentIt->lock();

			for (size_t index2 = index1 + 1; index2 < mPhysicsComponents.size(); ++index2)
			{
				std::list<std::weak_ptr<PhysicsComponent>>::iterator secondPhysicsComponentIt = mPhysicsComponents.begin();
				std::advance(secondPhysicsComponentIt, index2);

				if (!secondPhysicsComponentIt->expired())
				{
					std::shared_ptr<PhysicsComponent> secondPhysicsComponentToCheck = secondPhysicsComponentIt->lock();
					if (firstPhysicsComponentToCheck->IsCollisionDetected(*secondPhysicsComponentIt))
					{
						// @TODO
						firstPhysicsComponentToCheck->BroadcastCollisionEvents(secondPhysicsComponentToCheck->GetOwner(), { 0.0f,0.0f });
						secondPhysicsComponentToCheck->BroadcastCollisionEvents(firstPhysicsComponentToCheck->GetOwner(), { 0.0f,0.0f });

						firstPhysicsComponentToCheck->CollisionResolution();
						secondPhysicsComponentToCheck->CollisionResolution();

						ResolveWorldBounds(secondPhysicsComponentToCheck);
					}
				}
			}
			firstPhysicsComponentToCheck->DoPhysics(DeltaTime);
			ResolveWorldBounds(firstPhysicsComponentToCheck);
		}
	}
}

void PhysicsEngine::ResolveWorldBounds(const std::shared_ptr<PhysicsComponent>& component)
{
	auto Circle = std::dynamic_pointer_cast<CircleColliderComponent>(component);
	if (!Circle) return;

	auto Owner = Circle->GetOwner();
	auto OwnerSP = Owner.lock();
	if (!OwnerSP) return;

	auto TransformComp = OwnerSP->GetComponentOfType<TransformComponent>();
	if (!TransformComp) return;

	const float r = Circle->GetRadius();
	exVector2 pos = TransformComp->GetLocation();

	const float minX = r;
	const float maxX = kViewportWidth - r;
	const float minY = r;
	const float maxY = kViewportHeight - r;

	if (pos.x < minX) pos.x = minX;
	else if (pos.x > maxX) pos.x = maxX;

	if (pos.y < minY || pos.y > maxY)
	{
		if (pos.y < minY) pos.y = minY;
		else pos.y = maxY;

		TransformComp->SetLocation(pos);

		if (mOnOutOfBounds)
		{
			mOnOutOfBounds(Owner); 
		}
		return;
	}

	TransformComp->SetLocation(pos);
}

PhysicsEngine::PhysicsEngine()
{
}