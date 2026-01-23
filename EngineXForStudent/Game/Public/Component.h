#pragma once
#include "Game/Public/Utils.h"
#include "Game/Public/LifetimeInterface.h"

class Actor;

class Component : public ILifetimeInterface
{
	friend Actor;

public:

	Component() = delete;
	virtual ~Component();

protected:

	Component(std::weak_ptr<Actor> Owner);

	// Inherited from ILiftimeInterface
	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;
	virtual void EndPlay() override;
	// End ILiftimeInterface
	virtual bool CanAddComponent() const;

	std::weak_ptr<Actor> mOwner;


};

using ComponentList = std::list<std::shared_ptr<Component>>; 