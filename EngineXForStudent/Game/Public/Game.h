//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//
#pragma once
#include "Game/Public/Utils.h"
#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>

class Ball;
class Box;
class Text;
class Actor;
class GameManagerSystem;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

	// Game manager friendly APIs
	void						AddScore(int amount = 1);
	void						TriggerGameOver();
	std::shared_ptr<Ball>		GetPlayerBall() const;
	float						GetBallRadius() const;

private:

	exEngineInterface*			mEngine; 

	int							mFontID; // Font ID for score text
	int							mBigFontID; // Font ID for game over text

	bool						mUp;
	bool						mDown;

	exVector2					mTextPosition;
	std::shared_ptr<Ball>		mBall_First;
	std::shared_ptr<Ball>		mScoreBall;
	std::shared_ptr<Ball>		mGameOverBall;
	std::shared_ptr<Box>		mBox;

	// separate text actors
	std::shared_ptr<Text>		mScoreText;
	std::shared_ptr<Text>		mGameOverText;

	int							mScore;
	bool						mIsGameOver;

	// runtime helpers
	float						mBallRadius;

	// Add GameManagerSystem pointer
	std::unique_ptr<GameManagerSystem> mGameManager;
};
