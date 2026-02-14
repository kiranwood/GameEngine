#include "Game/Public/Actors/Line.h"
#include "Game/Public/Components/LineRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"

Line::Line(exVector2 StartPoint, exVector2 EndPoint, exColor LineColor)
{
	mStartPoint = StartPoint;
	mEndPoint = EndPoint;
	mLineColor = LineColor;
}

void Line::BeginPlay()
{
	AddComponentOfType<TransformComponent>(mStartPoint);
	AddComponentOfType<LineRenderComponent>(mLineColor, mStartPoint, mEndPoint);
}
