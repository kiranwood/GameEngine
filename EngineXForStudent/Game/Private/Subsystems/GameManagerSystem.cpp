#include "Game/Public/Subsystems/GameManagerSystem.h"
#include "Game/Public/Game.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include <memory>

GameManagerSystem::GameManagerSystem(MyGame* game)
	: mGame(game), mScore(0), mIsGameOver(false), mInitialized(false)
{
}

void GameManagerSystem::GameUpdate(float DeltaTime)
{
	if (!mGame)
		return;

	// Lazy initialize triggers once
	if (!mInitialized)
	{
		std::shared_ptr<Ball> player = mGame->GetPlayerBall();
		float radius = mGame->GetBallRadius();

		if (!player || radius <= 0.0f)
		{
			// wait until player exists and radius is set
			return;
		}

		// Score trigger
		{
			exVector2 scorePos{ 400.0f, 200.0f };
			std::shared_ptr<Actor> trigger = Actor::SpawnActorOfType<Actor>(scorePos);
			if (trigger)
			{
				auto result = trigger->AddComponentOfType<CircleColliderComponent>(radius, exVector2{0.0f,0.0f}, true, false);
				if (std::shared_ptr<CircleColliderComponent> Col = std::get<0>(result))
				{
					CollisionEventSignature ScoreDelegate = [this](std::weak_ptr<Actor> OtherActor, const exVector2)
					{
						if (!mGame)
							return;
						if (OtherActor.expired())
							return;
						if (std::shared_ptr<Actor> other = OtherActor.lock())
						{
							if (std::dynamic_pointer_cast<Ball>(other) == mGame->GetPlayerBall())
							{
								AddScore(1);
							}
						}
					};
					Col->ListenForCollision(ScoreDelegate);
				}
				mScoreTriggers.push_back(trigger);
			}
		}

		// Game over trigger
		{
			exVector2 gameOverPos{ 400.0f, 400.0f };
			std::shared_ptr<Actor> trigger = Actor::SpawnActorOfType<Actor>(gameOverPos);
			if (trigger)
			{
				auto result = trigger->AddComponentOfType<CircleColliderComponent>(radius, exVector2{0.0f,0.0f}, true, false);
				if (std::shared_ptr<CircleColliderComponent> Col = std::get<0>(result))
				{
					CollisionEventSignature GameOverDelegate = [this](std::weak_ptr<Actor> OtherActor, const exVector2)
					{
						if (!mGame)
							return;
						if (OtherActor.expired())
							return;
						if (std::shared_ptr<Actor> other = OtherActor.lock())
						{
							if (std::dynamic_pointer_cast<Ball>(other) == mGame->GetPlayerBall())
							{
								TriggerGameOver();
							}
						}
					};
					Col->ListenForCollision(GameOverDelegate);
				}
				mGameOverTriggers.push_back(trigger);
			}
		}

		mInitialized = true;
	}
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

