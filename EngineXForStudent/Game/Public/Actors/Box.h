#pragma once
#include "Game/Public/Actor.h"

class Box : public Actor
{
public:

	Box(float width, float height, exColor color, int renderLayer);

	virtual void BeginPlay() override;

private:

	// Box Size
	float mWidth;
	float mHeight;

	// Box traits
	exColor mColor;
	int mRenderLayer;
	exVector2 mPosition;
};
