#pragma once
#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

namespace Fumo = FumoEngine;
namespace Showcase
{
	class ShowCaseScene : public Fumo::BaseScene {
	public:
		std::string getName() const override;

		static void EnqueueBullet(Fumo::GameObject* obj);
		static Fumo::GameObject* DequeueBullet();

		static void EnqueueEnemy(Fumo::GameObject* obj);
		static Fumo::GameObject* DequeueEnemy();

		static void DebugSize();
		static float GenerateRandomFloat(float min, float max);
		static int GenerateRandomInt(int min, int max);

		static void GameOver(bool won);
		static void RestartGame();

		static int playerLives;
		static Fumo::GameObject* healthUI;
		static Fumo::GameObject* healthUI2;
		static Fumo::GameObject* healthUI3;

	protected:
		void initialize() override;
		void on_activate() override;
		void on_update(float deltaTime) override;


	private:
		static Fumo::GameObject* timerBar;
		static Fumo::GameObject* player;

		static Fumo::GameObject* winScreen;
		static Fumo::GameObject* loseScreen;

		static float maxLevelTime;
		static float levelTimer;
		static float spawnTimer;//Initial timer
		float shootCooldownTimer = 0.0f;

		static bool gameOver;

		static std::queue<Fumo::GameObject*> bulletPool;
		static std::queue<Fumo::GameObject*> enemyPool;

		static std::unordered_set<Fumo::GameObject*> activeBullets;
		static std::unordered_set<Fumo::GameObject*> activeEnemies;
	};
}


