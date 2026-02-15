#include "Game/Public/Actors/Text.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"

Text::Text(const std::string& InText, exColor InColor, int InFontID, exVector2 InPosition)
	: mText(InText)
	, mColor(InColor)
	, mFontID(InFontID)
	, mPosition(InPosition)
{
}

void Text::BeginPlay()
{
	// Add a transform at the requested position
	AddComponentOfType<TransformComponent>(mPosition);

	// Add text render component (color, font id, text, optional offset)
	AddComponentOfType<TextRenderComponent>(mColor, mText, mFontID, exVector2{ 0.0f, 0.0f });
}

void Text::EndPlay()
{
	AddComponentOfType<TransformComponent>(mPosition);

	AddComponentOfType<TextRenderComponent>(mColor, mText, mFontID, exVector2{ 0.0f, 0.0f });

}

void Text::SetText(const std::string& NewText)
{
	mText = NewText;
	// Optionally update the TextRenderComponent if it exists
	if (auto textComp = GetComponentOfType<TextRenderComponent>())
	{
		textComp->SetText(mText);
	}
}