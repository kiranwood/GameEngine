#pragma once
#include "Game/Public/Components/RenderComponent.h"

// Component to render a rectange/square
class BoxRenderComponent : public RenderComponent
{
	friend class Actor;

public:
	// Delete the default constructor
	BoxRenderComponent() = delete;

	// Override render function
	virtual void Render(exEngineInterface* EngineInterface) override;
protected:
	// Protected constructor
	BoxRenderComponent(std::weak_ptr<Actor> owner, exColor renderColor, float width, float height, int layer);

private:
	// Box size
	float mWidth;
	float mHeight;

	int mLayer;
};