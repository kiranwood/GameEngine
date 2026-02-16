#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class BottomPipeSection : public Actor
{
public:

	BottomPipeSection(float width, float height);
	~BottomPipeSection();

	virtual void BeginPlay() override;
	virtual void OnCollision(std::weak_ptr<Actor>, const exVector2);

private:

	// Box size
	float mWidth;
	float mHeight;

};