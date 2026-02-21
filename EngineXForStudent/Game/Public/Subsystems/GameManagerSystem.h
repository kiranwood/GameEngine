#pragma once
#include "Game/Public/Utils.h"
#include <vector>

// Manages score (touch BoxTrigger) and game over (touch TopPipeSection / BottomPipeSection).

class GameManagerSystem
{
public:
	GameManagerSystem(class MyGame* game);

	// Call once after the Pipe is spawned so we can hook its colliders
	void RegisterPipe(std::shared_ptr<class Pipe> pipe);

	// Called every frame from MyGame::Run
	void GameUpdate(float DeltaTime);

	// Score management
	void AddScore(int amount = 1);
	int  GetScore()  const;
	void ResetScore();

	// Game-over state
	void TriggerGameOver();
	bool IsGameOver()   const;
	void ResetGameOver();

private:
	class MyGame* mGame;

	int  mScore = 0;
	bool mIsGameOver = false;
};