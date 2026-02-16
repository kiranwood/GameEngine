#include "Game/Public/Actors/TopPipeSection.h"
#include "Game/Public/Components/BoxRenderComponent.h"
#include "Game/Public/Components/BoxColliderComponent.h"

TopPipeSection::TopPipeSection(float width, float height)
	: mWidth(width),
	mHeight(height)
{
}

TopPipeSection::~TopPipeSection()
{
}

void TopPipeSection::BeginPlay()
{
	// TODO: Delete later
	exColor Color1;
	Color1.mColor[0] = 92;
	Color1.mColor[1] = 230;
	Color1.mColor[2] = 92;
	Color1.mColor[3] = 255;

	// Binds collision function result
	AddComponentOfType<BoxRenderComponent>(Color1, mWidth, mHeight);
	std::tuple<std::shared_ptr<BoxColliderComponent>, bool, String> ResultBoxCollider = AddComponentOfType<BoxColliderComponent>(mWidth, mHeight);

	if (std::shared_ptr<BoxColliderComponent> BoxColliderComp = std::get<0>(ResultBoxCollider))
	{
		CollisionEventSignature CollisionDelegate = std::bind(&TopPipeSection::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		BoxColliderComp->ListenForCollision(CollisionDelegate);
	}
}

// Collision to call the score
void TopPipeSection::OnCollision(std::weak_ptr<Actor>, const exVector2)
{
	if (std::shared_ptr<RenderComponent> RenderComp = GetComponentOfType<RenderComponent>())
	{
		exColor Color;
		Color.mColor[0] = 90;
		Color.mColor[1] = 45;
		Color.mColor[2] = 230;
		Color.mColor[3] = 255;

		RenderComp->SetColor(Color);
	}
}