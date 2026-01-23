#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Ball : public Actor
{
public:

	Ball(float BallRadius, exColor BallColor, exVector2 BallCenter);

	void Render(exEngineInterface* EngineInterface) override;

	void SetBallPosition(const exVector2& NewPosition);
	exVector2 GetBallPosition() const;


private:

	float mRadius;
	exColor mColor;
	exVector2 mCenter;
};

