#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineInterface.h"	


class Line : public Actor
{
	public:
	Line(exVector2 StartPoint, exVector2 EndPoint, exColor LineColor);
	virtual void BeginPlay() override;

private:
	exVector2 mStartPoint;
	exVector2 mEndPoint;
	exColor mLineColor;
};
