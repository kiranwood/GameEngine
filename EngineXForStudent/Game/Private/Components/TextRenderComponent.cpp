#include "Game/Public/Components/TextRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

TextRenderComponent::TextRenderComponent(std::weak_ptr<Actor> owner,
    exColor RenderColor,
    const std::string& Text,
    int FontID,
    exVector2 Offset,
    int Layer)
    : RenderComponent(owner, RenderColor)
    , mText(Text)
    , mFontID(FontID)
    , mOffset(Offset)
    , mLayer(Layer)
{
}

void TextRenderComponent::Render(exEngineInterface* EngineInterface)
{
    // Defensive checks: if the engine or font is invalid, do nothing.
    if (!EngineInterface) return;
    if (mFontID < 0) return;

    // Default position if cannot resolve the owner's transform.
    exVector2 pos = { 0.0f, 0.0f };

    // lock owner -> fetch TransformComponent -> read location.
    if (!mOwner.expired())
    {
        if (std::shared_ptr<Actor> owner = mOwner.lock())
        {
            if (std::shared_ptr<TransformComponent> tr = owner->GetComponentOfType<TransformComponent>())
            {
                pos = tr->GetLocation();
            }
        }
    }

    // Apply local offset
    pos.x += mOffset.x;
    pos.y += mOffset.y;

    // EngineInterface signature
    EngineInterface->DrawText(mFontID, pos, mText.c_str(), mRenderColor, mLayer);
}
