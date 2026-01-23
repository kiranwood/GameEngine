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

	float Radius = 50.0f;
	exVector2 Center;
	Center.x = 300;
	Center.y = 400;

	exColor Color;
	Color.mColor[0] = 255;
	Color.mColor[1] = 50;
	Color.mColor[2] = 150;
	Color.mColor[3] = 255;

	mBall = std::make_shared<Ball>(Radius, Color, Center);
	mBall->AddComponentOfType<Component>();
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
	mBall->Render(mEngine);
	mTextPosition = mBall->GetBallPosition();

	if (mUp)
	{
		mTextPosition.y -= 20;
	}
	if (mDown)
	{
		mTextPosition.y += 20;
	}
	mBall->SetBallPosition(mTextPosition);
}
