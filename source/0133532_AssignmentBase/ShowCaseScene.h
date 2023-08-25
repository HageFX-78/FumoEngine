#pragma once
#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

class ShowCaseScene : public BaseScene {
public:
	std::string getName() const override;

	static void EnqueueBullet(GameObject* obj);
	static GameObject* DequeueBullet();

	static void EnqueueEnemy(GameObject* obj);
	static GameObject* DequeueEnemy();

	static void DebugSize();
	static float GenerateRandomFloat(float min, float max);
	static int GenerateRandomInt(int min, int max);

	static void GameOver(bool won);
	static void RestartGame();

	static int playerLives;
	static GameObject* healthUI;
	static GameObject* healthUI2;
	static GameObject* healthUI3;

protected:
	void initialize() override;
	void on_activate() override;
	void on_update(float deltaTime) override;
	
	
private:
	static GameObject* timerBar;
	static GameObject* player;

	static GameObject* winScreen;
	static GameObject* loseScreen;

	static float maxLevelTime;
	static float levelTimer;
	static float spawnTimer;//Initial timer
	float shootCooldownTimer = 0.0f;

	static bool gameOver;

	static std::queue<GameObject*> bulletPool;
	static std::queue<GameObject*> enemyPool;

	static std::unordered_set<GameObject*> activeBullets;
	static std::unordered_set<GameObject*> activeEnemies;
};

