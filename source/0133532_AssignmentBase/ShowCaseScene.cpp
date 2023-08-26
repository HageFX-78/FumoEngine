#define _USE_MATH_DEFINES
#include <cmath>
#include <random>

#include "ShowCaseScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "GameObjectCollection.h"
#include "Application.h"

#include "RendererComponent.h"
#include "SpriteRenderer.h"
#include "ProgressBar.h"
#include "CircleCollider.h"

namespace Showcase
{
	class EnemyCollider : public Fumo::CircleCollider {
	public:
		EnemyCollider(Fumo::GameObject* go, float rad = 30.0f, bool isVisible = false) : CircleCollider(go, rad, isVisible) {}

		void OnCollisionEnter(Fumo::GameObject& other) override {

			gameObject->setIsActive(false);
			isColliding = false;

			ShowCaseScene::EnqueueEnemy(gameObject);

			if (other.getTag() == Fumo::Bullet)
			{
				ShowCaseScene::EnqueueBullet(&other);
			}
			else if (other.getTag() == Fumo::Player)
			{
				ShowCaseScene::playerLives--;
				switch (ShowCaseScene::playerLives)
				{
				case 0:
					std::cout << "Game Over" << std::endl;
					ShowCaseScene::healthUI2->setIsActive(false);
					ShowCaseScene::GameOver(false);
					break;
				case 1:
					ShowCaseScene::healthUI->setIsActive(false);
					break;
				case 2:
					ShowCaseScene::healthUI3->setIsActive(false);
					break;
				default:
					std::cout << "Game Over" << std::endl;
					ShowCaseScene::healthUI->setIsActive(false);
					ShowCaseScene::GameOver(false);
				}
			}
			//ShowCaseScene::DebugSize();
		}
	};



#pragma region ShowCaseScene


	Fumo::GameObject* ShowCaseScene::healthUI;
	Fumo::GameObject* ShowCaseScene::healthUI2;
	Fumo::GameObject* ShowCaseScene::healthUI3;

	Fumo::GameObject* ShowCaseScene::timerBar;
	Fumo::GameObject* ShowCaseScene::player;

	Fumo::GameObject* ShowCaseScene::winScreen;
	Fumo::GameObject* ShowCaseScene::loseScreen;

	int ShowCaseScene::playerLives = 3;
	bool ShowCaseScene::gameOver = false;

	float ShowCaseScene::maxLevelTime = 60.0f;
	float ShowCaseScene::levelTimer = ShowCaseScene::maxLevelTime;
	float ShowCaseScene::spawnTimer = 5.0f;//Initial timer

	std::queue<Fumo::GameObject*> ShowCaseScene::bulletPool;
	std::queue<Fumo::GameObject*> ShowCaseScene::enemyPool;
	std::unordered_set<Fumo::GameObject*> ShowCaseScene::activeBullets;
	std::unordered_set<Fumo::GameObject*> ShowCaseScene::activeEnemies;

	std::string ShowCaseScene::getName() const {
		return "FUMONIA";
	}

	void ShowCaseScene::initialize() {
		player = new Fumo::GameObject("Player", Fumo::Player);
		player->addComponent<Fumo::SpriteRenderer>("../assets/player.png", Vector4(0.0f, 255.0f, 0.0f, 1.0f), Vector2(0.5f, 0.5f), Vector2(0.1f, 0.1f));
		player->addComponent<Fumo::CircleCollider>(15.0f);

		for (int x = 0; x < 20; x++)
		{
			Fumo::GameObject* newEnemy = new Fumo::GameObject("Fumo", Fumo::Enemy);
			newEnemy->addComponent<Fumo::SpriteRenderer>("../assets/fumo.png");
			newEnemy->addComponent<EnemyCollider>(35.0f);
			newEnemy->getComponent<EnemyCollider>()->addCollidableTag(Fumo::Player);
			newEnemy->getComponent<EnemyCollider>()->addCollidableTag(Fumo::Bullet);

			EnqueueEnemy(newEnemy);
		}

		for (int x = 0; x < 20; x++)
		{
			Fumo::GameObject* newBullet = new Fumo::GameObject("Bullet", Fumo::Bullet);
			newBullet->addComponent<Fumo::RendererComponent>(Fumo::Circle);
			newBullet->addComponent<Fumo::CircleCollider>(5.0f);

			EnqueueBullet(newBullet);
		}

		timerBar = new Fumo::GameObject("Timer");
		timerBar->addComponent<Fumo::ProgressBar>(Fumo::CenterHorizontal, Fumo::Application::instance->getWindowSize().x - 50.0f, 30.0f, 1.0f);
		timerBar->getComponent<Fumo::ProgressBar>()->setBothBarOpacity(0.5f);
		timerBar->getComponent<Fumo::ProgressBar>()->setBarColor(133.0f, 210.0f, 255.0f, 1.0f);
		timerBar->transform->setYPosition(Fumo::Application::instance->getWindowSize().y * 0.5f - 30.0f);

		healthUI = new Fumo::GameObject("HUI1");
		healthUI->addComponent<Fumo::SpriteRenderer>("../assets/player.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.2f, 0.2f));
		healthUI->transform->setPosition(0.0f, -Fumo::Application::instance->getWindowSize().y * 0.5f + 50.0f);
		healthUI->transform->setRotation(-45.0f);

		healthUI2 = new Fumo::GameObject("HUI2");
		healthUI2->addComponent<Fumo::SpriteRenderer>("../assets/player.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.2f, 0.2f));
		healthUI2->transform->setPosition(-100.0f, -Fumo::Application::instance->getWindowSize().y * 0.5f + 50.0f);
		healthUI2->transform->setRotation(-45.0f);

		healthUI3 = new Fumo::GameObject("HUI3");
		healthUI3->addComponent<Fumo::SpriteRenderer>("../assets/player.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.2f, 0.2f));
		healthUI3->transform->setPosition(100.0f, -Fumo::Application::instance->getWindowSize().y * 0.5f + 50.0f);
		healthUI3->transform->setRotation(-45.0f);

		winScreen = new Fumo::GameObject("WinScreen");
		winScreen->addComponent<Fumo::SpriteRenderer>("../assets/won.png");
		winScreen->setIsActive(false);

		loseScreen = new Fumo::GameObject("LoseScreen");
		loseScreen->addComponent<Fumo::SpriteRenderer>("../assets/lost.png");
		loseScreen->setIsActive(false);
	}

	void ShowCaseScene::on_activate() {
		glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);

		std::cout << std::endl << "< Move cursor around to aim >" << std::endl;
		std::cout << "[ W ][ A ][ S ][ D ] to move around" << std::endl;
		std::cout << "[ Space ]/[ Left Mouse Button ] to fire bullets (Hold Down)" << std::endl;
		std::cout << "[ R ] when game is over to restart the level" << std::endl;
		std::cout << "[ E ] to toggle collider visibility" << std::endl << std::endl;
	}

	void ShowCaseScene::on_update(float deltaTime) {
		// - - - - Level Timer

		if (!gameOver)
		{
			levelTimer -= deltaTime;
			timerBar->getComponent<Fumo::ProgressBar>()->setProgress(levelTimer / maxLevelTime);
		}
		if (levelTimer <= 0)
		{
			GameOver(true);
		}

		// - - - - -  Player rotate to mouse
		if (player)
		{
			float angleInDegrees = std::atan2(Fumo::Input::getMousePositionCentered().y - player->transform->getYPosition(),
				Fumo::Input::getMousePositionCentered().x - player->transform->getXPosition()) * (180.0f / M_PI);

			player->transform->setRotation(angleInDegrees - 90.0f);
		}


		// - - - - - -  Enemy Spawner
		Vector2 windowSize = Fumo::Application::instance->getWindowSize();

		if (!gameOver)
		{
			spawnTimer -= deltaTime;

			if (spawnTimer <= 0)
			{
				for (int x = 0; x < GenerateRandomInt(1, 5); x++)
				{
					Fumo::GameObject* newEnemy = DequeueEnemy();

					if (newEnemy)
					{
						int spawnSide = GenerateRandomInt(0, 3);

						float offsetFromBorder = 20.0f;
						float spawnX = 0.0f;
						float spawnY = 0.0f;

						switch (spawnSide)
						{
						case 0: // Top
							spawnX = GenerateRandomFloat(-windowSize.x * 0.5f, windowSize.x * 0.5f);
							spawnY = windowSize.y * 0.5f + offsetFromBorder;
							break;
						case 1: // Bottom
							spawnX = GenerateRandomFloat(-windowSize.x * 0.5f, windowSize.x * 0.5f);
							spawnY = -windowSize.y * 0.5f - offsetFromBorder;
							break;
						case 2: // Left
							spawnX = -windowSize.x * 0.5f - offsetFromBorder;
							spawnY = GenerateRandomFloat(-windowSize.y * 0.5f, windowSize.y * 0.5f);
							break;
						case 3: // Right
							spawnX = windowSize.x * 0.5f + offsetFromBorder;
							spawnY = GenerateRandomFloat(-windowSize.y * 0.5f, windowSize.y * 0.5f);
							break;
						}
						newEnemy->transform->setPosition(spawnX, spawnY);
					}
				}
				spawnTimer = GenerateRandomFloat(0.1f, 2.0f);
			}


			// - - - - - - - Enemy Movements
			for (Fumo::GameObject* enemy : activeEnemies)
			{
				if (!enemy->getIsActive()) continue;

				Vector2 playerPosition = player->transform->getPosition();
				Vector2 enemyPosition = enemy->transform->getPosition();

				Vector2 direction = Vector2(playerPosition.x - enemyPosition.x, playerPosition.y - enemyPosition.y);
				direction = Vector2::normalize(direction);

				float moveSpeed = 110.0f * deltaTime;

				//Set position to follow player constantly instead of having a single constant direction like bullets
				enemy->transform->setPosition(enemyPosition.x + direction.x * moveSpeed, enemyPosition.y + direction.y * moveSpeed);

			}
		}

		// - - - - - Bullet out of bounds
		for (auto it = activeBullets.begin(); it != activeBullets.end();)
		{
			Fumo::GameObject* bulletObj = *it;

			if (bulletObj->transform->getXPosition() > windowSize.x ||
				bulletObj->transform->getXPosition() < -windowSize.x ||
				bulletObj->transform->getYPosition() > windowSize.y ||
				bulletObj->transform->getYPosition() < -windowSize.y)
			{
				it = activeBullets.erase(it);
				EnqueueBullet(bulletObj);
			}
			else ++it;
		}

		//  - - - -  Scene Input handling
		if (Fumo::Input::getKey(GLFW_KEY_D))
		{
			player->transform->setXPosition(player->transform->getXPosition() + 100.0f * deltaTime);
		}
		else if (Fumo::Input::getKey(GLFW_KEY_A))
		{
			player->transform->setXPosition(player->transform->getXPosition() - 100.0f * deltaTime);
		}
		if (Fumo::Input::getKey(GLFW_KEY_W))
		{
			player->transform->setYPosition(player->transform->getYPosition() + 100.0f * deltaTime);
		}
		else if (Fumo::Input::getKey(GLFW_KEY_S))
		{
			player->transform->setYPosition(player->transform->getYPosition() - 100.0f * deltaTime);
		}
		if (Fumo::Input::getKeyDown(GLFW_KEY_R) && gameOver)
		{
			RestartGame();
		}
		if (Fumo::Input::getKeyDown(GLFW_KEY_E))
		{
			Fumo::CircleCollider::globalShowCollider = !Fumo::CircleCollider::globalShowCollider;
		}

		//  - - - - - Shoot
		shootCooldownTimer -= deltaTime;
		if (Fumo::Input::getKey(GLFW_KEY_SPACE) || Fumo::Input::getMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			if (shootCooldownTimer <= 0)
			{
				Fumo::GameObject* bullet = DequeueBullet();
				if (bullet)
				{
					bullet->transform->setPosition(player->transform->getPosition());
					bullet->setIsActive(true);

					Vector2 direction(
						cos((player->transform->getRotation() + 90.0f) * (M_PI / 180.0f)),
						sin((player->transform->getRotation() + 90.0f) * (M_PI / 180.0f))
					);
					direction = Vector2::normalize(direction);

					bullet->transform->setVelocity(Vector2(direction.x * 300.0f, direction.y * 300.0f));
				}
				shootCooldownTimer = 0.25f;
			}
		}
	}

	void ShowCaseScene::EnqueueBullet(Fumo::GameObject* obj)
	{
		obj->setIsActive(false);
		obj->transform->setPosition(0, 0);
		activeBullets.erase(obj);
		bulletPool.push(obj);

	}

	Fumo::GameObject* ShowCaseScene::DequeueBullet()
	{
		if (bulletPool.empty()) return nullptr;

		Fumo::GameObject* deqObj = bulletPool.front();
		bulletPool.pop();
		activeBullets.insert(deqObj);
		deqObj->setIsActive(true);

		return deqObj;
	}

	void ShowCaseScene::EnqueueEnemy(Fumo::GameObject* obj)
	{
		obj->setIsActive(false);
		obj->transform->setPosition(0, 0);
		activeEnemies.erase(obj);
		enemyPool.push(obj);
	}

	Fumo::GameObject* ShowCaseScene::DequeueEnemy()
	{
		if (enemyPool.empty()) return nullptr;

		Fumo::GameObject* deqObj = enemyPool.front();
		enemyPool.pop();
		activeEnemies.insert(deqObj);
		deqObj->setIsActive(true);

		return deqObj;
	}

	void ShowCaseScene::DebugSize()
	{
		std::cout << "Bullet pool current size: " << bulletPool.size() << std::endl;
		std::cout << "Enemy pool current size: " << enemyPool.size() << std::endl;
	}

	float ShowCaseScene::GenerateRandomFloat(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> distribution(min, max);

		return distribution(gen);
	}
	int ShowCaseScene::GenerateRandomInt(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(min, max);

		return distribution(gen);
	}

	void ShowCaseScene::GameOver(bool won)
	{
		gameOver = true;
		for (auto it = activeEnemies.begin(); it != activeEnemies.end();)
		{
			Fumo::GameObject* enemyObj = *it;
			it = activeEnemies.erase(it);
			EnqueueEnemy(enemyObj);
		}
		if (won)
		{
			winScreen->setIsActive(true);
		}
		else
		{
			loseScreen->setIsActive(true);
		}
	}
	void ShowCaseScene::RestartGame()
	{
		timerBar->getComponent<Fumo::ProgressBar>()->setProgress(1.0f);
		healthUI->setIsActive(true);
		healthUI2->setIsActive(true);
		healthUI3->setIsActive(true);

		player->transform->setPosition(0, 0);
		levelTimer = maxLevelTime;

		winScreen->setIsActive(false);
		loseScreen->setIsActive(false);

		playerLives = 3;

		gameOver = false;

	}
#pragma endregion
}
