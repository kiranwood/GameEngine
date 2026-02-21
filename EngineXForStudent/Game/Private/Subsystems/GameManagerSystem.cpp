#include "Game/Public/Subsystems/GameManagerSystem.h"
#include "Game/Public/Game.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Actors/Bird.h"
#include "Game/Public/Actors/Pipe.h"
#include "Game/Public/Actors/BoxTrigger.h"
#include "Game/Public/Actors/TopPipeSection.h"
#include "Game/Public/Actors/BottomPipeSection.h"
#include "Game/Public/Components/BoxColliderComponent.h"
#include <memory>

GameManagerSystem::GameManagerSystem(MyGame* game)
	: mGame(game), mScore(0), mIsGameOver(false)
{
}

void GameManagerSystem::RegisterPipe(std::shared_ptr<Pipe> pipe)
{
	if (!pipe) return;

	if (std::shared_ptr<BoxTrigger> trigger = pipe->GetTrigger())
	{
		if (std::shared_ptr<BoxColliderComponent> col =
			trigger->GetComponentOfType<BoxColliderComponent>())
		{
			CollisionEventSignature onScore =
				[this](std::weak_ptr<Actor> other, const exVector2)
				{
					if (mIsGameOver) return;
					if (other.expired()) return;
					// Only score when it is the player ball
					if (std::dynamic_pointer_cast<Bird>(other.lock()))
					{
						AddScore(1);
					}
				};
			col->ListenForCollision(onScore);
		}
	}

	// ---- Game-over triggers (top and bottom pipe sections) ----
	auto registerGameOver = [this](std::shared_ptr<Actor> section)
		{
			if (!section) return;
			if (std::shared_ptr<BoxColliderComponent> col =
				section->GetComponentOfType<BoxColliderComponent>())
			{
				CollisionEventSignature onGameOver =
					[this](std::weak_ptr<Actor> other, const exVector2)
					{
						if (mIsGameOver) return;
						if (other.expired()) return;
						if (std::dynamic_pointer_cast<Bird>(other.lock()))
						{
							TriggerGameOver();
						}
					};
				col->ListenForCollision(onGameOver);
			}
		};

	registerGameOver(pipe->GetTopPipe());
	registerGameOver(pipe->GetBotPipe());
}

void GameManagerSystem::GameUpdate(float /*DeltaTime*/)
{
	// Future: spawn new pipes, reset on restart, etc.
}

void GameManagerSystem::AddScore(int amount)
{
	mScore += amount;
}

int GameManagerSystem::GetScore() const
{
	return mScore;
}

void GameManagerSystem::ResetScore()
{
	mScore = 0;
}


void GameManagerSystem::TriggerGameOver()
{
	mIsGameOver = true;
}

bool GameManagerSystem::IsGameOver() const
{
	return mIsGameOver;
}

void GameManagerSystem::ResetGameOver()
{
	mIsGameOver = false;
}