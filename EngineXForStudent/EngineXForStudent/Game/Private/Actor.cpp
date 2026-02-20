#include "Game/Public/Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{	// TODO
}

void Actor::EndPlay()
{
}

void Actor::Tick(const float DeltaSeconds)
{
	for (std::shared_ptr<Component> ComponentIt : mComponents)
	{
		ComponentIt->Tick(DeltaSeconds);
	}
	// TODO
}
