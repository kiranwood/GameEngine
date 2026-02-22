#include "Game/Public/Actors/PipeSection.h"
#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Actors/Box.h"

PipeSection::PipeSection(float width, float height, bool IsTopSection)
	: mWidth(width),
	mHeight(height),
	mPosition(exVector2()),
	mIsTopSection(IsTopSection)
{
	// Sets Pipe Green
	mPipeGreen.mColor[0] = 29;
	mPipeGreen.mColor[1] = 209;
	mPipeGreen.mColor[2] = 71;
	mPipeGreen.mColor[3] = 255;

	// Pipe Higlight Green
	mPipeHighlightGreen.mColor[0] = 35;
	mPipeHighlightGreen.mColor[1] = 225;
	mPipeHighlightGreen.mColor[2] = 75;
	mPipeHighlightGreen.mColor[3] = 255;
	
	// Pipe Yellow 
	mPipeYellow.mColor[0] = 201;
	mPipeYellow.mColor[1] = 192;
	mPipeYellow.mColor[2] = 52;
	mPipeYellow.mColor[3] = 255;

	// Pipe Yellow Higlight
	mPipeYellowHighlight.mColor[0] = 222;
	mPipeYellowHighlight.mColor[1] = 212;
	mPipeYellowHighlight.mColor[2] = 80;
	mPipeYellowHighlight.mColor[3] = 255;

}

PipeSection::~PipeSection()
{
}

void PipeSection::BeginPlay()
{
	if (std::shared_ptr<TransformComponent> transformComp = GetComponentOfType<TransformComponent>()) mPosition = transformComp->GetLocation();

	float x = mPosition.x;
	float y = mPosition.y;
	float innerPosY;
	if (mIsTopSection) innerPosY = mPosition.y + (mHeight / 2);
	else innerPosY = mPosition.y - (mHeight / 2);

	// Creates boxes main pipe section
	mOuterSection = Actor::SpawnActorOfType<Box>(exVector2(x, y), mWidth, mHeight - 20, mPipeGreen, 3);
	mHighlightOuterSection = Actor::SpawnActorOfType<Box>(exVector2(x - 5, y), mWidth - 20, mHeight - 20, mPipeHighlightGreen, 2);

	// Creates boxes for top of pipe
	mInnerSection = Actor::SpawnActorOfType<Box>(exVector2(x, innerPosY), mWidth + 10, 20, mPipeYellow, 3);
	mHighlightInnerSection = Actor::SpawnActorOfType<Box>(exVector2(x - 5, innerPosY), mWidth - 10, 20, mPipeYellowHighlight, 2);
}

void PipeSection::ApplyCollisionEvent(CollisionEventSignature collisionEvent)
{
	// Applies collision event to both colliders for pipe
	if (std::shared_ptr<BoxColliderComponent> col = mInnerSection->GetComponentOfType<BoxColliderComponent>())
	{
		col->ListenForCollision(collisionEvent);
	}

	if (std::shared_ptr<BoxColliderComponent> col = mOuterSection->GetComponentOfType<BoxColliderComponent>())
	{
		col->ListenForCollision(collisionEvent);
	}
}

void PipeSection::ApplyVelocity(exVector2 velocity)
{
	// Applies velocity to both parts of pipe

	if (std::shared_ptr<PhysicsComponent> physicsComp = mOuterSection->GetComponentOfType<PhysicsComponent>())
	{
		physicsComp->SetVelocity(velocity);
	}

	if (std::shared_ptr<PhysicsComponent> physicsComp = mHighlightOuterSection->GetComponentOfType<PhysicsComponent>())
	{
		physicsComp->SetVelocity(velocity);
	}

	if (std::shared_ptr<PhysicsComponent> physicsComp = mInnerSection->GetComponentOfType<PhysicsComponent>())
	{
		physicsComp->SetVelocity(velocity);
	}

	if (std::shared_ptr<PhysicsComponent> physicsComp = mHighlightInnerSection->GetComponentOfType<PhysicsComponent>())
	{
		physicsComp->SetVelocity(velocity);
	}
}

