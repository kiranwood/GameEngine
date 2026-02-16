#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class TopPipeSection : public Actor
{
public:

	TopPipeSection(float width, float height);
	~TopPipeSection();

	virtual void BeginPlay() override;
	virtual void OnCollision(std::weak_ptr<Actor>, const exVector2);

private:

	// Box size
	float mWidth;
	float mHeight;

};