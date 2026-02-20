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
class Bird;
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

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	enum InputBits : unsigned char
	{
		INPUT_NONE = 0,
		INPUT_FLAP = 1 << 0,
	};

	unsigned char mInputMask;
	std::shared_ptr<Bird> mBird;

	exVector2					mTextPosition;
};
