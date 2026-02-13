#pragma once
#include "Game/Public/Utils.h"

class GameManagerSystem
{
public:
	GameManagerSystem() = delete;
	GameManagerSystem(std::shared_ptr<class MyGame> game);

	// called every frame from MyGame (or wherever subsystems are ticked)
	void GameUpdate(float DeltaTime);

private:
	void SpawnPipePair();
	void CleanupOffscreen();

private:
	std::shared_ptr<class MyGame> mGame;

	// runtime state
	bool						mInitialized = false;
	float						mTimeSinceLastSpawn = 0.0f;
	float						mSpawnInterval = 2.0f;		// seconds between spawns
	float						mPipeSpeed = 2.0f;			// horizontal speed (pixels per tick / frame unit)
	float						mGapSize = 120.0f;			// vertical gap between score/gameover circles
	float						mSpawnXOffset = 50.0f;		// spawn off-screen offset

	// spawned actors to manage lifetime
	std::vector<std::shared_ptr<class Actor>> mSpawnedActors;

	// random
	std::mt19937				mRng;
	std::uniform_real_distribution<float> mYDist;
};