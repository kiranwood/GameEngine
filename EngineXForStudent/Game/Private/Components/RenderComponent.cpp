#include "Game/Public/Components/RenderComponent.h"

void RenderComponent::Render(exEngineInterface* EngineInterface)
{
}

RenderComponent::RenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor)
	: Component(owner),
	mRenderColor(RenderColor)
{
}
