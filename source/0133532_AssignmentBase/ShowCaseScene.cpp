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



class EnemyCollider : public CircleCollider {
public:
	EnemyCollider(GameObject* go, float rad = 30.0f, bool isVisible = false) : CircleCollider(go, rad, isVisible) {}

	void OnCollisionEnter(GameObject& other) override {

		gameObject->setIsActive(false);
		isColliding = false;

		ShowCaseScene::EnqueueEnemy(gameObject);

		if (other.getTag() == Bullet)
		{
			ShowCaseScene::EnqueueBullet(&other);
		}
		else if (other.getTag() == Player)
		{
			ShowCaseScene::playerLives--;
			switch (ShowCaseScene::playerLives)
			{
				case 0:
					std::cout << "Game Over" << std::endl;
					ShowCaseScene::healthUI->setIsActive(false);
					ShowCaseScene::GameOver(false);
					break;
				case 1:
					ShowCaseScene::healthUI2->setIsActive(false);
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


GameObject* ShowCaseScene::healthUI;
GameObject* ShowCaseScene::healthUI2;
GameObject* ShowCaseScene::healthUI3;

GameObject* ShowCaseScene::timerBar;
GameObject* ShowCaseScene::player;

GameObject* ShowCaseScene::winScreen;
GameObject* ShowCaseScene::loseScreen;

int ShowCaseScene::playerLives = 3;
bool ShowCaseScene::gameOver = false;

float ShowCaseScene::maxLevelTime = 60.0f;
float ShowCaseScene::levelTimer = ShowCaseScene::maxLevelTime;
float ShowCaseScene::spawnTimer = 5.0f;//Initial timer

std::queue<GameObject*> ShowCaseScene::bulletPool;
std::queue<GameObject*> ShowCaseScene::enemyPool;
std::unordered_set<GameObject*> ShowCaseScene::activeBullets;
std::unordered_set<GameObject*> ShowCaseScene::activeEnemies;

std::string ShowCaseScene::getName() const {
	return "FUMONIA";
}

void ShowCaseScene::initialize() {
	player = new GameObject("Player", Player);
	player->addComponent<SpriteRenderer>("../assets/player.png", Vector4(0.0f, 255.0f, 0.0f, 1.0f), Vector2(0.5f, 0.5f), Vector2(0.1f, 0.1f));
	player->addComponent<CircleCollider>(15.0f);

	for (int x = 0; x < 20; x++)
	{
		GameObject* newEnemy = new GameObject("Fumo", Enemy);
		newEnemy->addComponent<SpriteRenderer>("../assets/fumo.png");
		newEnemy->addComponent<EnemyCollider>(35.0f, true);
		newEnemy->getComponent<EnemyCollider>()->addCollidableTag(Player);
		newEnemy->getComponent<EnemyCollider>()->addCollidableTag(Bullet);

		EnqueueEnemy(newEnemy);
	}

	for (int x = 0; x < 20; x++)
	{
		GameObject* newBullet = new GameObject("Bullet", Bullet);
		newBullet->addComponent<RendererComponent>(Circle);
		newBullet->addComponent<CircleCollider>(5.0f, true);

		EnqueueBullet(newBullet);
	}

	timerBar = new GameObject("Timer");
	timerBar->addComponent<ProgressBar>(Application::instance->getWindowSize().x - 50.0f, 30.0f, 1.0f);
	timerBar->getComponent<ProgressBar>()->setBothBarOpacity(0.5f);
	timerBar->transform->setYPosition(Application::instance->getWindowSize().y * 0.5f - 30.0f);

	healthUI = new GameObject("HUI1");
	healthUI->addComponent<SpriteRenderer>("../assets/player.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.2f, 0.2f));
	healthUI->transform->setPosition(0.0f, -Application::instance->getWindowSize().y * 0.5f + 50.0f);
	healthUI->transform->setRotation(-45.0f);

	healthUI2 = new GameObject("HUI2");
	healthUI2->addComponent<SpriteRenderer>("../assets/player.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.2f, 0.2f));
	healthUI2->transform->setPosition(-100.0f, -Application::instance->getWindowSize().y * 0.5f + 50.0f);
	healthUI2->transform->setRotation(-45.0f);

	healthUI3 = new GameObject("HUI3");
	healthUI3->addComponent<SpriteRenderer>("../assets/player.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.2f, 0.2f));
	healthUI3->transform->setPosition(100.0f, -Application::instance->getWindowSize().y * 0.5f + 50.0f);
	healthUI3->transform->setRotation(-45.0f);

	winScreen = new GameObject("WinScreen");
	winScreen->addComponent<SpriteRenderer>("../assets/won.png");
	winScreen->setIsActive(false);

	loseScreen = new GameObject("LoseScreen");
	loseScreen->addComponent<SpriteRenderer>("../assets/lost.png");
	loseScreen->setIsActive(false);
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {
	// - - - - Level Timer

	if (!gameOver)
	{
		levelTimer -= deltaTime;
		timerBar->getComponent<ProgressBar>()->setProgress(levelTimer / maxLevelTime);
	}
	if (levelTimer <= 0)
	{
		GameOver(true);
	}

	// - - - - -  Player rotate to mouse
	if (player)
	{
		float angleInDegrees = std::atan2(Input::getMousePositionCentered().y - player->transform->getYPosition(),
			Input::getMousePositionCentered().x - player->transform->getXPosition()) * (180.0f / M_PI);

		player->transform->setRotation(angleInDegrees - 90.0f);
	}


	// - - - - - -  Enemy Spawner
	Vector2 windowSize = Application::instance->getWindowSize();

	if (!gameOver)
	{
		spawnTimer -= deltaTime;

		if (spawnTimer <= 0)
		{
			for (int x = 0; x < GenerateRandomInt(1, 5); x++)
			{
				GameObject* newEnemy = DequeueEnemy();

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
			spawnTimer = GenerateRandomFloat(0.2f, 2.0f);
		}


		// - - - - - - - Enemy Movements
		for (GameObject* enemy : activeEnemies)
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
		GameObject* bulletObj = *it;

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
	if (Input::getKey(GLFW_KEY_D))
	{
		player->transform->setXPosition(player->transform->getXPosition() + 100.0f * deltaTime);
	}
	else if (Input::getKey(GLFW_KEY_A))
	{
		player->transform->setXPosition(player->transform->getXPosition() - 100.0f * deltaTime);
	}
	if (Input::getKey(GLFW_KEY_W))
	{
		player->transform->setYPosition(player->transform->getYPosition() + 100.0f * deltaTime);
	}
	else if (Input::getKey(GLFW_KEY_S))
	{
		player->transform->setYPosition(player->transform->getYPosition() - 100.0f * deltaTime);
	}

	//  - - - - - Shoot
	shootCooldownTimer -= deltaTime;
	if (Input::getKey(GLFW_KEY_SPACE) || Input::getMouseButton(GLFW_MOUSE_BUTTON_1))
	{
		if (shootCooldownTimer <= 0)
		{
			GameObject* bullet = DequeueBullet();
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
			shootCooldownTimer = 0.2f;
		}

	}
	if (Input::getKeyDown(GLFW_KEY_R) && gameOver)
	{
		RestartGame();
	}
	if (Input::getKeyDown(GLFW_KEY_E))
	{
		//Debug
	}
}

void ShowCaseScene::EnqueueBullet(GameObject* obj)
{
	obj->setIsActive(false);
	obj->transform->setPosition(0, 0);
	activeBullets.erase(obj);
	bulletPool.push(obj);

}

GameObject* ShowCaseScene::DequeueBullet()
{
	if (bulletPool.empty()) return nullptr;

	GameObject* deqObj = bulletPool.front();
	bulletPool.pop();
	activeBullets.insert(deqObj);
	deqObj->setIsActive(true);

	return deqObj;
}

void ShowCaseScene::EnqueueEnemy(GameObject* obj)
{
	obj->setIsActive(false);
	obj->transform->setPosition(0, 0);
	activeEnemies.erase(obj);
	enemyPool.push(obj);
}

GameObject* ShowCaseScene::DequeueEnemy()
{
	if (enemyPool.empty()) return nullptr;

	GameObject* deqObj = enemyPool.front();
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
	std::random_device rd; // Seed for the random number generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<float> distribution(min, max);

	// Generate a random number in the specified range
	float randomValue = distribution(gen);

	return randomValue;
}
int ShowCaseScene::GenerateRandomInt(int min, int max)
{
	std::random_device rd; // Seed for the random number generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<int> distribution(min, max);

	// Generate a random number in the specified range
	int randomValue = distribution(gen);

	return randomValue;
}

void ShowCaseScene::GameOver(bool won)
{
	gameOver = true;
	for (auto it = activeEnemies.begin(); it != activeEnemies.end();)
	{
		GameObject* enemyObj = *it;
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
	timerBar->getComponent<ProgressBar>()->setProgress(1.0f);
	healthUI->setIsActive(true);
	healthUI2->setIsActive(true);
	healthUI3->setIsActive(true);

	player->transform->setPosition(0, 0);
	levelTimer = maxLevelTime;

	winScreen->setIsActive(false);
	loseScreen->setIsActive(false);

	gameOver = false;

}
#pragma endregion