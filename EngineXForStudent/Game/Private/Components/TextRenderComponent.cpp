#include "Game/Public/Components/TextRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"

void TextRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (!EngineInterface)
		return;

	if (mOwner.expired())
		return;

	if (std::shared_ptr<Actor> owner = mOwner.lock())
	{
		exVector2 pos = { 0.0f, 0.0f };
		if (std::shared_ptr<TransformComponent> TransformComp = owner->GetComponentOfType<TransformComponent>())
		{
			pos = TransformComp->GetLocation();
		}

		// apply local offset
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		EngineInterface->DrawText(mFontID, pos, mText.c_str(), mRenderColor, 1);
	}
}

TextRenderComponent::TextRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, int FontID, const std::string& Text, exVector2 Offset)
	: RenderComponent(owner, RenderColor)
	, mFontID(FontID)
	, mText(Text)
	, mOffset(Offset)
{
}