#pragma once

#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

// Ball with gravity and impulse
class Bird : public Actor
{
public:
    Bird(float Radius, exColor Color);
    virtual void BeginPlay() override;

    // Upwards impulse
    void Flap();

    void SetFlapImpulse(float impulse) { mFlapImpulse = impulse; }

private:
    float   mRadius = 20.0f;
    exColor mColor{};

    // Vertical speed (px/s)
    float   mFlapImpulse = 350.0f;
};
