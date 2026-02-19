#include "Game/Public/Subsystems/PipeSpawner.h"
#include "Game/Public/Actors/Pipe.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"
#include <cstdlib>   // rand, RAND_MAX
#include <ctime>     // time

// Initializes the spawner with the given parameters and seeds the random generator.
PipeSpawner::PipeSpawner(float spawnInterval,
	float pipeSpeed,
	float spawnX,
	std::function<void(std::shared_ptr<Pipe>)> onPipeSpawned)
	: mSpawnInterval(spawnInterval)
	, mPipeSpeed(pipeSpeed)
	, mSpawnX(spawnX)
	, mTimer(0.0f)        // start timer at 0 so first pipe spawns after one full interval
	, mOnPipeSpawned(onPipeSpawned)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Spawn one pipe immediately so the screen isn't empty at the start
	SpawnPipe();
}


// Moves active pipes, removes off-screen pipes, and spawns new pipes at intervals.
void PipeSpawner::Update(float deltaTime, bool isGameOver)
{
	if (isGameOver) return;

	// Tick all active pipes so they move
	for (std::shared_ptr<Pipe>& pipe : mActivePipes)
	{
		if (pipe)
		{
			pipe->Tick(deltaTime);
		}
	}

	// Remove pipes that have scrolled off the left edge
	mActivePipes.erase(
		std::remove_if(mActivePipes.begin(), mActivePipes.end(),
			[this](const std::shared_ptr<Pipe>& pipe)
			{
				return IsOffScreen(pipe);
			}),
		mActivePipes.end());

	// Advance spawn timer and spawn a new pipe when the interval elapses
	mTimer += deltaTime;
	if (mTimer >= mSpawnInterval)
	{
		mTimer = 0.0f;
		SpawnPipe();
	}
}

// Destroys all tracked pipes and resets the spawn timer (call on game reset).
void PipeSpawner::Reset()
{
	mActivePipes.clear();
	mTimer = 0.0f;
}

// Spawns a new pipe at mSpawnX with a random y gap centre, and registers it.
void PipeSpawner::SpawnPipe()
{
	// Pick a random y centre for the gap
	float t = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	float gapY = kMinGapY + t * (kMaxGapY - kMinGapY);

	exVector2 spawnPos{ mSpawnX, gapY };

	// SpawnActorOfType<Pipe>(TransformLocation, Pipe::position, Pipe::speed)
	std::shared_ptr<Pipe> newPipe =
		Actor::SpawnActorOfType<Pipe>(spawnPos, spawnPos, mPipeSpeed);

	if (newPipe)
	{
		mActivePipes.push_back(newPipe);

		// Notify Game.cpp so it can register collision listeners
		if (mOnPipeSpawned)
		{
			mOnPipeSpawned(newPipe);
		}
	}
}

// Checks if the pipe has scrolled entirely off the left edge (past kDestroyX).
bool PipeSpawner::IsOffScreen(const std::shared_ptr<Pipe>& pipe) const
{
	if (!pipe) return true;

	// Use the Pipe actor's own TransformComponent (set by SpawnActorOfType)
	// as a cheap proxy for horizontal position
	if (std::shared_ptr<TransformComponent> tr =
		pipe->GetComponentOfType<TransformComponent>())
	{
		return tr->GetLocation().x < kDestroyX;
	}

	return false;
}