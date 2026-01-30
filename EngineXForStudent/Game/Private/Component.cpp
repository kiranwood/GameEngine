#include "Game/Public/Component.h"
#include "Game/Public/Actor.h"


Component::~Component()
{
}

std::weak_ptr<Actor> Component::GetOwner() const
{
	return mOwner;
}

Component::Component(std::weak_ptr<Actor> Owner) : mOwner(Owner)
{
}

void Component::BeginPlay()
{
	
	if (!mOwner.expired()) 
	{
		std::cout << "Component Owner" << mOwner.lock().get() << std::endl;
	}

}

void Component::Tick(const float DeltaTime)
{
	//TODO
}


void Component::EndPlay()
{
	//TODO
}

bool Component::CanAddComponent() const
{
	return true;
}


