#include "Game/Public/Components/BoxRenderComponent.h"
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineInterface.h"

// Constructor
BoxRenderComponent::BoxRenderComponent(std::weak_ptr<Actor> owner, exColor renderColor, float width, float height, int layer) :
	RenderComponent(owner, renderColor),
	mWidth(width),
	mHeight(height),
	mLayer(layer)
{
}

void BoxRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface) // Check for interface
	{
		if (!mOwner.expired()) // Checks if owner exists
		{
			if (std::shared_ptr<Actor> owner = mOwner.lock()) // Gets shared ptr of owner
			{
				if (std::shared_ptr<TransformComponent> TransformComp = owner->GetComponentOfType<TransformComponent>())
				{
					exVector2 CenterPos = TransformComp->GetLocation();

					float halfHeight = mHeight / 2;
					float halfWidth = mWidth / 2;

					exVector2 topLeftPos = { -halfWidth, -halfHeight };
					exVector2 bottomRightPos = { halfWidth, halfHeight };

					topLeftPos += CenterPos;
					bottomRightPos += CenterPos;

					EngineInterface->DrawBox(topLeftPos, bottomRightPos, mRenderColor, mLayer);
				}
			}
		}
	}
}
