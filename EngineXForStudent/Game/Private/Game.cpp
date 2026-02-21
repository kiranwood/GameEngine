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
#include "Game/Public/Actors/BoxTrigger.h"
#include "Game/Public/Actors/Pipe.h"
#include "Game/Public/Actors/Bird.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Subsystems/RenderSystem.h"
#include "Game/Public/Subsystems/GameManagerSystem.h"
#include "Game/Public/Subsystems/PipeSpawner.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Flappy Bird";

//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------

static constexpr float kPipeSpeed = 100.0f;   // pixels per frame the pipe scrolls left
static constexpr float kPipeSpawnInterval = 2.0f;   // seconds between new pipes
static constexpr float kPipeSpawnX = 800.0f; // just off the right edge of the screen


MyGame::MyGame()
	: mEngine(nullptr)
	, mFontID(-1) // invalid font id to start until loaded in Initialize()
	, mBigFontID(-1) // invalid font id to start until loaded in Initialize()
	, mUp(false)
	, mDown(false)
	, mScore(0)
	, mIsGameOver(false)
	, mBallRadius(0.0f)
	, mGameManager(nullptr)
	, mPipeSpawner(nullptr)
	, mGameState(GAMESTART)
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

	// Load fonts: small for score, big for game-over
	mFontID = mEngine->LoadFont( "Resources/JosefinSans-Regular.ttf", 32 );
	mBigFontID = mEngine->LoadFont( "Resources/JosefinSans-Regular.ttf", 64 );

	// Everything run from top left
	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	float Radius = 15.0f;
	mBallRadius = Radius;

	exColor Color1;
	Color1.mColor[0] = 255;
	Color1.mColor[1] = 50;
	Color1.mColor[2] = 150;
	Color1.mColor[3] = 255;

	// Player ball
	//mBall_First = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 350.0f), 2, Color1);

	// Creates a random trigger

	// Create Pipe
	//mPipe = Actor::SpawnActorOfType<Pipe>(exVector2(600.0f, 350.0f), exVector2(600, 350.0f), 1.0f);
	//mPipe.reset();

	mBird = Actor::SpawnActorOfType<Bird>(
		exVector2(kViewportWidth * 0.5f, kViewportHeight * 0.5f),
		Radius,
		Color1
	);

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

	// Initialize GameManagerSystem
	mGameManager = std::make_unique<GameManagerSystem>(this);
	mPipeSpawner = std::make_unique<PipeSpawner>(
		kPipeSpawnInterval,
		kPipeSpeed,
		kPipeSpawnX,
		[this](std::shared_ptr<Pipe> newPipe)
		{
			if (mGameManager)
			{
				mGameManager->RegisterPipe(newPipe);
			}
		}
	);

	// Creates game over text
	mTitleText = std::make_shared<Text>(
		std::string("Flappy Bird"), goTextColor, mBigFontID, exVector2{ 225.0f, 250.0f });
	mTitleText->BeginPlay();

	
	// Creates text to let player know
	mInputText = std::make_shared<Text>(
		std::string("Press Space to Start"), goTextColor, mFontID, exVector2{ 250.0f, 400.0f });
	mInputText->BeginPlay();
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
	if (pEvent->type == SDL_KEYDOWN)
	{
		if (pEvent->key.keysym.scancode == SDL_SCANCODE_SPACE && pEvent->key.repeat == 0)
		{
			mInputMask |= INPUT_SPACE; // Performs OR operation
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

// Like update function. Runs every frame
void MyGame::Run( float fDeltaT ) // How much time between frames
{
	// Runs section of game based on state
	switch (mGameState)
	{
		case 0:
			GameStart(fDeltaT);
			break;
		case 1:
			MainGame(fDeltaT);
			break;
		case 2:
			GameOver(fDeltaT);
			break;
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
}

// Title of game
void MyGame::GameStart(float fDeltaT)
{

	// Press space to start game
	if (mInputMask & INPUT_SPACE)
	{
		mTitleText.reset();
		mInputText.reset();
		mGameState = GAMEMAIN;
	}
}

// Main Game
void MyGame::MainGame(float fDeltaT)
{
	if (mInputMask & INPUT_SPACE)
	{
		if (mBird) mBird->Flap(); // If pointer exists, execute member method.
		mInputMask &= ~INPUT_SPACE; // Clears mInputMask member.
	}

	// --- Pipe spawner: ticks all live pipes, removes off-screen ones,
	//     and spawns new ones on the interval. Stops when game over. ---
	if (mPipeSpawner)
	{
		mPipeSpawner->Update(fDeltaT, mIsGameOver);
	}

	// --- Physics step (moves everything, fires collision events) ---
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);

	// --- Render step ---
	RENDER_ENGINE.RenderUpdate(mEngine);

	// --- Game manager: sync score text, detect game over ---
	if (mGameManager)
	{
		mGameManager->GameUpdate(fDeltaT);

		// Update score display when it changes
		int currentScore = mGameManager->GetScore();
		if (currentScore != mScore)
		{
			mScore = currentScore;
			if (mScoreText)
			{
				if (std::shared_ptr<TextRenderComponent> textComp =
					mScoreText->GetComponentOfType<TextRenderComponent>())
				{
					textComp->SetText("Score: " + std::to_string(mScore));
				}
			}
		}

		// Show "Game Over!" the first frame the condition is set
		if (mGameManager->IsGameOver() && !mIsGameOver)
		{
			mIsGameOver = true;

			mGameState = GAMEOVER;
		}
	}
}

// Game Over
void MyGame::GameOver(float fDeltaT)
{
	exColor goTextColor{ 255, 50, 50, 255 };

	// Creates game over text
	mGameOverText = std::make_shared<Text>(
		std::string("Game Over!"), goTextColor, mBigFontID, exVector2{ 225.0f, 250.0f });
	mGameOverText->BeginPlay();
}


void MyGame::AddScore(int amount)
{
	if (mGameManager)
	{
		mGameManager->AddScore(amount);
	}
}

void MyGame::TriggerGameOver()
{
	if (mGameManager)
	{
		mGameManager->TriggerGameOver();
	}
}

std::shared_ptr<Bird> MyGame::GetPlayerBall() const
{
	return mBird;
}

float MyGame::GetBallRadius() const
{
	return 20.0f;
}

std::shared_ptr<Pipe> MyGame::GetPipe() const
{
	return mPipe;
}