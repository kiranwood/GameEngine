#pragma once
#include "Game/Public/Utils.h"

class Actor;
class PhysicsComponent;

#define PHYSICS_ENGINE PhysicsEngine::GetInstance()

class PhysicsEngine
{

public:

	~PhysicsEngine();
	static PhysicsEngine& GetInstance()
	{
		if (!sPhysicsEngine)
		{
			sPhysicsEngine.reset(new PhysicsEngine());
		}
		return *sPhysicsEngine;
	}

	void AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd);
	void ResolveWorldBounds(const std::shared_ptr<PhysicsComponent>& component);
	void ClearInvalidPhysicsComponents();

	void PhysicsUpdate(const float DeltaTime);

	using OutOfBoundsCallback = std::function<void(std::weak_ptr<Actor>)>;
	void SetOutOfBoundsCallback(OutOfBoundsCallback cb) { mOnOutOfBounds = std::move(cb); }

private:

	PhysicsEngine();


	PhysicsEngine(const PhysicsEngine& OtherEngine) = delete;
	PhysicsEngine& operator=(const PhysicsEngine& OtherEngine) = delete;

	static std::unique_ptr<PhysicsEngine> sPhysicsEngine;

	std::list<std::weak_ptr<PhysicsComponent>> mPhysicsComponents;

	OutOfBoundsCallback mOnOutOfBounds;
};