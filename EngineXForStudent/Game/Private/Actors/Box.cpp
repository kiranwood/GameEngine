#include "Game/Public/Actors/Box.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/BoxRenderComponent.h"
#include "Game/Public/Components/BoxColliderComponent.h"

Box::Box(float width, float height, exColor color, int renderLayer) :
	mWidth(width),
	mHeight(height),
	mColor(color),
	mPosition(exVector2()),
	mRenderLayer(renderLayer)
{ }

// Called when game starts
void Box::BeginPlay()
{
	if (std::shared_ptr<TransformComponent> transformComp = GetComponentOfType<TransformComponent>()) mPosition = transformComp->GetLocation();

	// Adds renderer and collider
	AddComponentOfType<BoxRenderComponent>(mColor, mWidth, mHeight, mRenderLayer);
	AddComponentOfType<BoxColliderComponent>(mWidth, mHeight);

	
}
