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
#include <string>

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
	: mEngine( nullptr )
	, mFontID(-1) // invalid font id to start until loaded in Initialize()
	, mBigFontID( -1 ) // invalid font id to start until loaded in Initialize()
	, mUp( false )
	, mDown( false )
	, mScore(0)
	, mIsGameOver(false)
	, mBallRadius(0.0f)
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

	// Load fonts: small for score, big for game-over
	mFontID = mEngine->LoadFont( "Resources/JosefinSans-Regular.ttf", 32 );
	mBigFontID = mEngine->LoadFont( "Resources/JosefinSans-Regular.ttf", 64 );

	// Everything run from top left
	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	float Radius = 25.0f;
	mBallRadius = Radius;

	exColor Color1;
	Color1.mColor[0] = 255;
	Color1.mColor[1] = 50;
	Color1.mColor[2] = 150;
	Color1.mColor[3] = 255;

	// Player ball
	mBall_First = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 300.0f), Radius, Color1);

	// Create the score text (top-left)
	exVector2 scoreTextPos{ 50.0f, 20.0f };
	exColor scoreTextColor{ 255, 255, 255, 255 };
	mScoreText = std::make_shared<Text>(std::string("Score: 0"), scoreTextColor, mFontID, scoreTextPos);
	mScoreText->BeginPlay();

	// Create the centered Game Over text (initially empty)
	// approximate center positioning using viewport constants
	exVector2 gameOverPos{ 225.0f, 250.0f };
	exColor goTextColor{ 255, 50, 50, 255 };
	mGameOverText = std::make_shared<Text>(std::string(""), goTextColor, mBigFontID, gameOverPos);
	mGameOverText->EndPlay(); // dont show until game over

	// Score trigger: spawn invisible trigger ball
	exVector2 scorePos{ 200.0f, 200.0f };
	exColor triggerColor{ 0, 0, 0, 0 }; // invisible
	

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

void MyGame::OnEvent(SDL_Event* pEvent) // called for each event polled from SDL
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
	// Tick only the player ball if it exists
	if (mBall_First)
	{
		mBall_First->Tick(fDeltaT);
	}

	exVector2 BallVelocity(0.0f, 0.0f);

	if (mUp)
	{
		BallVelocity.y -= 2.5f;
	}
	if (mDown)
	{
		BallVelocity.y = 2.5f;
	}
	

	// only allow player control while not game over
	if (!mIsGameOver)
	{
		if (mBall_First)
		{
			if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_First->GetComponentOfType<PhysicsComponent>())
			{
				BallPhysicsComp->SetVelocity(BallVelocity);
			}
		}
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);

	RENDER_ENGINE.RenderUpdate(mEngine);
}
