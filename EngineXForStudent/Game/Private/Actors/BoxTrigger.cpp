#include "Game/Public/Actors/BoxTrigger.h"
#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Components/BoxRenderComponent.h"

BoxTrigger::BoxTrigger(float width, float height)
	: mWidth(width),
	mHeight(height)
{
}

BoxTrigger::~BoxTrigger()
{
}

// Adds a collider to the trigger
void BoxTrigger::BeginPlay()
{
	std::tuple<std::shared_ptr<BoxColliderComponent>, bool, String> ResultBoxCollider = AddComponentOfType<BoxColliderComponent>(mWidth, mHeight);

	// Binds collision function result
	if (std::shared_ptr<BoxColliderComponent> BoxColliderComp = std::get<0>(ResultBoxCollider))
	{
		CollisionEventSignature CollisionDelegate = std::bind(&BoxTrigger::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		BoxColliderComp->ListenForCollision(CollisionDelegate);
	}
}

// Collision to call the score
void BoxTrigger::OnCollision(std::weak_ptr<Actor>, const exVector2)
{
}