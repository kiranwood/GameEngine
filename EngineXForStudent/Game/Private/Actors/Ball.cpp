#include "Game/Public/Actors/Ball.h"

Ball::Ball(float BallRadius, exColor BallColor, exVector2 BallCenter)
{
	mRadius = BallRadius;
	mColor = BallColor;
	mCenter = BallCenter;
}

void Ball::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		EngineInterface->DrawCircle(mCenter, mRadius, mColor, 2);
	}
}

void Ball::SetBallPosition(const exVector2& NewPosition)
{
	mCenter = NewPosition;
}

exVector2 Ball::GetBallPosition() const
{
	return mCenter;
}
