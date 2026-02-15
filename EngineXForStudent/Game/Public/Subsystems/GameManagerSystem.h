#pragma once
#include "Game/Public/Utils.h"
#include <vector>

//Manages the game state when the player loses ("game over" condition).
//Handles score management (updating, storing, etc.).

class GameManagerSystem
{
public:
	GameManagerSystem(class MyGame* game);

	// called every frame from MyGame (or wherever subsystems are ticked)
	void GameUpdate(float DeltaTime);

	// Score management
	void AddScore(int amount = 1);
	int GetScore() const;
	void ResetScore();

	// Game over state management
	void TriggerGameOver();
	bool IsGameOver() const;
	void ResetGameOver();

private:
	class MyGame* mGame;
	std::vector<std::shared_ptr<class Actor>> mScoreTriggers;
	std::vector<std::shared_ptr<class Actor>> mGameOverTriggers;

	// runtime state
	int mScore = 0;
	bool mIsGameOver = false;
	bool mInitialized = false;
};