#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Box : public Actor
{
public:

	Box(float width, float height, exColor color);

	virtual void BeginPlay() override;

private:

	// Box Size
	float mWidth;
	float mHeight;

	// Box Color
	exColor mColor;
};
