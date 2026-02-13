#pragma once
#include "Game/Public/Utils.h"

//Manages the game state when the player loses ("game over" condition).
//Handles score management (updating, storing, etc.).


class GameManagerSystem
{
public:
	GameManagerSystem() = delete;
	GameManagerSystem(std::shared_ptr<class MyGame> game);

	// called every frame from MyGame (or wherever subsystems are ticked)
	void GameUpdate(float DeltaTime);

private:

private:
	std::shared_ptr<class MyGame> mGame;

	// runtime state


	std::vector<std::shared_ptr<class Actor>> mScoreTriggers;
	std::vector<std::shared_ptr<class Actor>> mGameOverTriggers;

};