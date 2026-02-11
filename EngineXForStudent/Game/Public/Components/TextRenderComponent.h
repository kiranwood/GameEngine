#pragma once
#include "Game/Public/Components/RenderComponent.h"
#include <string>

class TextRenderComponent : public RenderComponent
{
	friend class Actor;

public:
	TextRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

	// allow runtime updates of the shown text
	void SetText(const std::string& Text);

protected:
	TextRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, int FontID, const std::string& Text, exVector2 Offset = { 0.0f, 0.0f });

private:
	int mFontID;
	std::string mText;
	exVector2 mOffset;
};
