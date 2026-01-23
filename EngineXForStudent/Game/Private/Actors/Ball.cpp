#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"

Ball::Ball(float BallRadius, exColor BallColor)
{
	mRadius = BallRadius;
	mColor = BallColor;
}

void Ball::BeginPlay()
{
	AddComponentOfType<TransformComponent>(exVector2{ 200.0f, 300.0f });
	AddComponentOfType<CircleRenderComponent>(exColor({ 0, 255, 255, 255 }), 100.0f);
}
