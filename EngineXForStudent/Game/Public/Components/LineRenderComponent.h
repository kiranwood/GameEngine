#pragma once
#include "Game/Public/Components/RenderComponent.h"

class LineRenderComponent : public RenderComponent
{
	friend class Actor;

public:
	LineRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

protected:
	LineRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, exVector2 StartPoint, exVector2 EndPoint);

private:
	exVector2 mStartPoint;
	exVector2 mEndPoint;
};
