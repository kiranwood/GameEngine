#pragma once
#include "Game/Public/Actor.h"

class PipeSection;
class BottomPipeSection;
class BoxTrigger;

class Pipe : public Actor
{
public:

	Pipe(float speed);
	~Pipe();

	virtual void BeginPlay() override;
	virtual void Tick(float fDeltaT) override;

	// Accessors so GameManagerSystem can register collision listeners
	std::shared_ptr<PipeSection>    GetTopPipe()  const { return mTopPipe; }
	std::shared_ptr<PipeSection>	GetBotPipe()  const { return mBotPipe; }
	std::shared_ptr<BoxTrigger>		GetTrigger()  const { return mTrigger; }

private:
	   
	exVector2 mPosition;
	std::shared_ptr<PipeSection> mTopPipe;
	std::shared_ptr<PipeSection> mBotPipe;
	std::shared_ptr<BoxTrigger> mTrigger;

	float mSpeed;
	float mLifetime;
};