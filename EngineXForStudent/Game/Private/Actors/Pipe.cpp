#include "Game/Public/Actors/Pipe.h"
#include "Game/Public/Actors/PipeSection.h"
#include "Game/Public/Actors/BoxTrigger.h"

Pipe::Pipe(float speed)
	: mPosition(exVector2()),
	mSpeed(speed),
	mLifetime(0.0f)
{
}

Pipe::~Pipe()
{
}

void Pipe::BeginPlay()
{
	if (std::shared_ptr<TransformComponent> transformComp = GetComponentOfType<TransformComponent>()) mPosition = transformComp->GetLocation();

	float x = mPosition.x;
	float y = mPosition.y;

	// Creates each component of pipe
	mTopPipe = Actor::SpawnActorOfType<PipeSection>(exVector2(x, y - 575), 40.0f, 1000.0f, true);
	mBotPipe = Actor::SpawnActorOfType<PipeSection>(exVector2(x, y + 575), 40.0f, 1000.0f, false);
	mTrigger = Actor::SpawnActorOfType<BoxTrigger>(exVector2(x, y), 40.0f, 150.0f);
}

// Moves each component by a set speed
void Pipe::Tick(float fDeltaT)
{
	exVector2 velocity = exVector2(-mSpeed, 0.0f);

	if (mTopPipe) mTopPipe->ApplyVelocity(velocity);
	if (mBotPipe) mBotPipe->ApplyVelocity(velocity);


	if (std::shared_ptr<PhysicsComponent> PipePhysics = mTrigger->GetComponentOfType<PhysicsComponent>())
	{
		PipePhysics->SetVelocity(velocity);
	}
}

exVector2 Pipe::GetPosition()
{
	if (std::shared_ptr<TransformComponent> transform = mTrigger->GetComponentOfType<TransformComponent>())
	{
		return transform->GetLocation();
	}
}
