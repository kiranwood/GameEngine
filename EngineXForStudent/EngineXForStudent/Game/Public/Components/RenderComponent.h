#pragma once
#include "Game/Public/Component.h"
#include <type_traits>
#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

class RenderComponent : public Component, public std::enable_shared_from_this<RenderComponent>
{
	friend class Actor;

public:
	RenderComponent() = delete;

	virtual void BeginPlay() override;
	virtual void Render(exEngineInterface* EngineInterface);

	void SetColor(exColor newColor);

protected:
	RenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor);
	exColor mRenderColor;
};