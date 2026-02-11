//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/Box.h"
#include "Game/Public/Actors/Text.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Subsystems/RenderSystem.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr ) // Handle anything to do with rendering
	, mFontID( -1 ) // Handle is a font id
	, mUp( false )
	, mDown( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	// You can load multiple fonts
	mFontID = mEngine->LoadFont( "Resources/JosefinSans-Regular.ttf", 32 );

	// Everything run from top left
	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	float Radius = 25.0f;

	exColor Color1;
	Color1.mColor[0] = 255;
	Color1.mColor[1] = 50;
	Color1.mColor[2] = 150;
	Color1.mColor[3] = 255;

	exColor Color2;
	Color2.mColor[0] = 255;
	Color2.mColor[1] = 150;
	Color2.mColor[2] = 50;
	Color2.mColor[3] = 255;

	mBall_First = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 300.0f), Radius, Color1);

	mBall_Second = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 100.0f), Radius, Color2);

	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_Second->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsComp->SetVelocity(exVector2(0.0f, 0.5f));
	}

	//mBall->AddComponentOfType<TransformComponent>(Center);

	/*mBox = std::make_shared<Box>(200.0f, 500.0f, Color1);
	mBox->BeginPlay();
	mBox->AddComponentOfType<Component>();*/

	// Create a Text actor and begin play (score display)
	exVector2 textPos{ 50.0f, 20.0f };
	exColor textColor{ 255, 255, 255, 255 };
	mText = std::make_shared<Text>(std::string("Score: 0"), textColor, mFontID, textPos);
	mText->BeginPlay();

	// Register score increment on collision: register only one collider so each collision counts once
	if (std::shared_ptr<CircleColliderComponent> Collider = mBall_First->GetComponentOfType<CircleColliderComponent>())
	{
		// Need an lvalue to pass by non-const ref
		CollisionEventSignature ScoreDelegate = [this](std::weak_ptr<Actor>, const exVector2)
			{
				++mScore;
				if (std::shared_ptr<TextRenderComponent> TextComp = mText->GetComponentOfType<TextRenderComponent>())
				{
					std::string s = "Score: " + std::to_string(mScore);
					TextComp->SetText(s);
				}
			};

		Collider->ListenForCollision(ScoreDelegate);
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Whenever you play the game the window name will show
const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Can have RBG colour for anything
void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	// Uses bits
	mUp = pState[SDL_SCANCODE_UP]; // Enum to be readable
	mDown = pState[SDL_SCANCODE_DOWN];
	
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Like update function. Runs every frame
void MyGame::Run( float fDeltaT ) // How much time between frames
{
	mBall_First->Tick(fDeltaT);


	mBall_Second->Tick(fDeltaT);

	/*if (std::shared_ptr<RenderComponent> RenderComp = mBox->GetComponentOfType<RenderComponent>())
	{
		RenderComp->Render(mEngine);
	}
	mBox->Tick(fDeltaT);*/

	exVector2 BallVelocity(0.0f, 0.0f);

	if (mUp)
	{
		
		BallVelocity.y -=2.5f;
	}
	if (mDown)
	{
		BallVelocity.y = 2.5f;
	}

	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_First->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsComp->SetVelocity(BallVelocity);
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);

	RENDER_ENGINE.RenderUpdate(mEngine);
}
