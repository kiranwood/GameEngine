#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

class RenderComponent : public Component
{
	friend class Actor;

public:
	RenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface);

protected:

	RenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor);
	exColor mRenderColor;

};

