#pragma once

#include "Game/Public/Components/RenderComponent.h"
#include <string>

// Renders a text string through the engine.
// By default, the text is positioned using the owner's TransformComponent, plus an optional screen/world offset.
class TextRenderComponent : public RenderComponent
{
    friend class Actor; // Actor::AddComponentOfType<T> needs access to the protected ctor

public:
    TextRenderComponent() = delete;

    // Called by the game render.
    // Uses EngineInterface->DrawText(...) to draw the stored string.
    virtual void Render(exEngineInterface* EngineInterface) override;

    // Add SetText for runtime updates
    void SetText(const std::string& NewText) { mText = NewText; }

protected:
    // Owner is injected by Actor; FontID must come from EngineInterface->LoadFont(...).
    TextRenderComponent(std::weak_ptr<Actor> owner,
        exColor RenderColor,
        const std::string& Text,
        int FontID,
        exVector2 Offset = { 0.0f, 0.0f },
        int Layer = 1);

private:
    std::string mText;  // Stored text
    int mFontID;        // Font handle returned by LoadFont(...)
    exVector2 mOffset;  // Applied after owner's position
    int mLayer;         // Render layer order (engine-defined)
};
