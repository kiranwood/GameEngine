#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Box;

class PipeSection : public Actor
{
public:

	PipeSection(float width, float height, bool IsTopSection);
	~PipeSection();

	virtual void BeginPlay() override;
	virtual void ApplyCollisionEvent(CollisionEventSignature collisionEvent);
	virtual void ApplyVelocity(exVector2 velocity);

protected:

	// Box size
	float mWidth;
	float mHeight;

	exColor mPipeGreen;
	exColor mPipeYellow;

	exVector2 mPosition;
	std::shared_ptr<Box> mInnerSection;
	std::shared_ptr<Box> mOuterSection;

	bool mIsTopSection;
};