#include "Game/Public/Actors/Bird.h"

#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"

Bird::Bird(float Radius, exColor Color)
    : mRadius(Radius)
    , mColor(Color)
{
}

void Bird::BeginPlay()
{
    AddComponentOfType<CircleRenderComponent>(mColor, mRadius);

    // (radius, velocity, isStatic, isGravityEnabled)
    auto [Collider, bOk, Msg] = AddComponentOfType<CircleColliderComponent>(
        mRadius,
        exVector2{ 0.0f, 0.0f },
        false,
        true
    );

    // only vertical movement
    if (Collider)
    {
        Collider->SetVelocity(exVector2{ 0.0f, 0.0f });
    }
}

void Bird::Flap()
{
    if (auto Phys = GetComponentOfType<PhysicsComponent>())
    {
        exVector2 v = Phys->GetVelocity();
        v.x = 0.0f;
        v.y = -mFlapImpulse; // up = Y negative
        Phys->SetVelocity(v);
    }
}