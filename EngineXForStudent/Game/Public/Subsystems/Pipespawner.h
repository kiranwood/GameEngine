#pragma once
#include "Game/Public/Utils.h"
#include <vector>
#include <functional>

class Pipe;
class GameManagerSystem;

class PipeSpawner
{
public:

	PipeSpawner(float spawnInterval,
		float pipeSpeed,
		float spawnX,
		std::function<void(std::shared_ptr<Pipe>)> onPipeSpawned = nullptr);

	// Call every frame from MyGame::Run (before physics update).
	// Does nothing if the game is over.
	void Update(float deltaTime, bool isGameOver);

	// Destroy all tracked pipes (call on game reset).
	void Reset();

private:
	// Spawn one pipe at a random y gap centre and register it.
	void SpawnPipe();

	// Returns true when a pipe has scrolled entirely off the left edge.
	bool IsOffScreen(const std::shared_ptr<Pipe>& pipe) const;

	float mSpawnInterval;   // seconds between spawns
	float mPipeSpeed;       // speed forwarded to Pipe constructor
	float mSpawnX;          // x position for new pipes
	float mTimer;           // counts up to mSpawnInterval

	std::vector<std::shared_ptr<Pipe>> mActivePipes;

	// Fires once per spawned pipe so Game.cpp can wire collision listeners
	std::function<void(std::shared_ptr<Pipe>)> mOnPipeSpawned;

	// Off screen threshold on the left side (pipe is gone past this x)
	static constexpr float kDestroyX = -100.0f;

	// Vertical range for the gap centre
	static constexpr float kMinGapY = 150.0f;
	static constexpr float kMaxGapY = 500.0f;
};