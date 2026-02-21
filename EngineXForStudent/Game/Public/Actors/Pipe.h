#pragma once
#include "Game/Public/Actor.h"

class TopPipeSection;
class BottomPipeSection;
class BoxTrigger;

class Pipe : public Actor
{
public:

	Pipe(exVector2 position, float speed);
	~Pipe();

	virtual void BeginPlay() override;
	virtual void Tick(float fDeltaT) override;

	// Accessors so GameManagerSystem can register collision listeners
	std::shared_ptr<TopPipeSection>    GetTopPipe()  const { return mTopPipe; }
	std::shared_ptr<BottomPipeSection> GetBotPipe()  const { return mBotPipe; }
	std::shared_ptr<BoxTrigger>        GetTrigger()  const { return mTrigger; }
	//Nick was here
	
	

private:
	   
	exVector2 mPosition;
	std::shared_ptr<TopPipeSection> mTopPipe;
	std::shared_ptr<BottomPipeSection> mBotPipe;
	std::shared_ptr<BoxTrigger> mTrigger;

	float mSpeed;
	float mLifetime;
};