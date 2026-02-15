#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"
#include <string>

class Text : public Actor
{
public:
	Text() = delete;
	Text(const std::string& InText, exColor InColor, int InFontID, exVector2 InPosition);
	virtual void BeginPlay() override;
	virtual void EndPlay() override;

	// Add SetText for runtime text update
	void SetText(const std::string& NewText);

private:
	std::string mText;
	exColor mColor;
	int mFontID; // Font ID from engine
	exVector2 mPosition;
};
