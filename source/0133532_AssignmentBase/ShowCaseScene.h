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
	/// <summary>
	/// A simple shooter survival game where you have to survive a horde of fumo by firing at them under 60 seconds.<br><br>
	/// It is to showcase the extent of functionality of Fumo Engine
	/// </summary>
	class ShowCaseScene : public Fumo::BaseScene {
	public:
		std::string getName() const override;

		static void EnqueueBullet(Fumo::GameObject* obj);
		static Fumo::GameObject* DequeueBullet();

		static void EnqueueEnemy(Fumo::GameObject* obj);
		static Fumo::GameObject* DequeueEnemy();
		
		static void DebugSize();
		/// <summary>
		/// Generate random float using Mersenne Twister engine, first line gets a random number from the hardware itself
		/// and provides it to the engine in the second line. Both min and max values are inclusive.
		/// </summary>
		/// <param name="min">Minimum value (Inclusive)</param>
		/// <param name="max">Maximum value (Inclusive)</param>
		/// <returns></returns>
		static float GenerateRandomFloat(float min, float max);
		/// <summary>
		/// Generate random int using Mersenne Twister engine, first line gets a random number from the hardware itself
		/// and provides it to the engine in the second line. Both min and max values are inclusive.
		/// </summary>
		/// <param name="min">Minimum value (Inclusive)</param>
		/// <param name="max">Maximum value (Inclusive)</param>
		/// <returns></returns>
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

		/// <summary>
		/// Bullet object pool
		/// </summary>
		static std::queue<Fumo::GameObject*> bulletPool;
		/// <summary>
		/// Enemy object pool
		/// </summary>
		static std::queue<Fumo::GameObject*> enemyPool;

		/// <summary>
		/// Collection of active bullets to call logic on in the scene and pool
		/// </summary>
		static std::unordered_set<Fumo::GameObject*> activeBullets;
		/// <summary>
		/// Collection of active enemies to call logic on in the scene and pool
		/// </summary>
		static std::unordered_set<Fumo::GameObject*> activeEnemies;
	};
}


