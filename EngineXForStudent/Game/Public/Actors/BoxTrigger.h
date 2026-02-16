#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class BoxTrigger : public Actor
{
public:

	BoxTrigger(float width, float height);
	~BoxTrigger();

	virtual void BeginPlay() override;
	virtual void OnCollision(std::weak_ptr<Actor>, const exVector2);

private:

	// Box size
	float mWidth;
	float mHeight;

};