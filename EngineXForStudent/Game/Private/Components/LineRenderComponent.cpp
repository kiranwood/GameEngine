#include "Game/Public/Components/LineRenderComponent.h"
#include "Engine/Public/EngineInterface.h"

void LineRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		EngineInterface->DrawLine(mStartPoint, mEndPoint, mRenderColor, 1);
	}
}

LineRenderComponent::LineRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, exVector2 StartPoint, exVector2 EndPoint)
	: RenderComponent(owner, RenderColor), mStartPoint(StartPoint), mEndPoint(EndPoint)
{
}
