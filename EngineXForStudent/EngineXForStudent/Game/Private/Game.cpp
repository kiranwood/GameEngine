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
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Subsystems/RenderSystem.h"
//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "PG29 Game Engine";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
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

	mFontID = mEngine->LoadFont( "Resources/afternight.ttf", 32 );

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

	mBall_First = Actor::SpawnActorOfType<Ball>( exVector2(200.0f,300.0f), Radius, Color1);

	mBall_Second = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 100.0f), Radius, Color2);


	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_Second->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsComp->SetVelocity(exVector2(0.0f, 0.5f));
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

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

	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	exVector2 BallVelocity(0.0f,0.0f);
	if (mUp)
	{
		BallVelocity.y = -2.5f;
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
