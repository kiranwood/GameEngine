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
#include "Game/Public/Actors/Bird.h"
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
	, mInputMask(0)
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

	mBird = Actor::SpawnActorOfType<Bird>(
		exVector2(kViewportWidth * 0.5f, kViewportHeight * 0.5f),
		Radius,
		Color1
	);
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
	if (pEvent->type == SDL_KEYDOWN)
	{
		if (pEvent->key.keysym.scancode == SDL_SCANCODE_SPACE && pEvent->key.repeat == 0)
		{
			mInputMask |= INPUT_FLAP; // Performs OR operation
		}
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	if (mInputMask & INPUT_FLAP)
	{
		if (mBird) mBird->Flap(); // If pointer exists, execute member method.
		mInputMask &= ~INPUT_FLAP; // Clears mInputMask member.
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
}
