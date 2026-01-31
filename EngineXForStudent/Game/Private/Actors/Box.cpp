#include "Game/Public/Actors/Box.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/BoxRenderComponent.h"

Box::Box(float width, float height, exColor color) :
	mWidth(width),
	mHeight(height),
	mColor(color)
{ }

// Called when game starts
void Box::BeginPlay()
{
	AddComponentOfType<TransformComponent>(exVector2{ 200.0f, 300.0f });
	AddComponentOfType<BoxRenderComponent>(mColor, mWidth, mHeight);
}
