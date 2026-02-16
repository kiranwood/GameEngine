#include "Game/Public/Actors/Pipe.h"
#include "Game/Public/Actors/BottomPipeSection.h"
#include "Game/Public/Actors/TopPipeSection.h"
#include "Game/Public/Actors/BoxTrigger.h"

Pipe::Pipe(exVector2 position, float speed)
	: mPosition(position),
	mSpeed(speed),
	mLifetime(0.0f)
{

	float x = mPosition.x;
	float y = mPosition.y;

	// Creates each component of pipe
	mTopPipe = Actor::SpawnActorOfType<TopPipeSection>(exVector2(x, y-575), 40.0f, 1000.0f);
	mBotPipe = Actor::SpawnActorOfType<BottomPipeSection>(exVector2(x, y+575), 40.0f, 1000.0f);
	mTrigger = Actor::SpawnActorOfType<BoxTrigger>(exVector2(x, y), 40.0f, 150.0f);
}

Pipe::~Pipe()
{
}

void Pipe::BeginPlay()
{
	  
}

// Moves each component by a set speed
void Pipe::Tick(float fDeltaT)
{
	exVector2 velocity = exVector2(-mSpeed, 0.0f);

	if (std::shared_ptr<PhysicsComponent> PipePhysics = mTopPipe->GetComponentOfType<PhysicsComponent>())
	{
		PipePhysics->SetVelocity(velocity);
	}


	if (std::shared_ptr<PhysicsComponent> PipePhysics = mBotPipe->GetComponentOfType<PhysicsComponent>())
	{
		PipePhysics->SetVelocity(velocity);
	}


	if (std::shared_ptr<PhysicsComponent> PipePhysics = mTrigger->GetComponentOfType<PhysicsComponent>())
	{
		PipePhysics->SetVelocity(velocity);
	}
}
