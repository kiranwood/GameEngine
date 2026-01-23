#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Ball : public Actor
{
public:

	Ball(float BallRadius, exColor BallColor);


	virtual void BeginPlay() override;

private:

	float mRadius;
	exColor mColor;
};

