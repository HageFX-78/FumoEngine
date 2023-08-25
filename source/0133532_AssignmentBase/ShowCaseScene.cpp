#define _USE_MATH_DEFINES
#include <cmath>

#include "ShowCaseScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "GameObjectCollection.h"

#include "RendererComponent.h"
#include "SpriteRenderer.h"
#include "ProgressBar.h"
#include "CircleCollider.h"


class EnemyCollider : public CircleCollider {
public:
	EnemyCollider(GameObject* go, float rad = 30.0f, bool isVisible = false) : CircleCollider(go, rad, isVisible) {}

	void OnCollisionEnter(GameObject& other) override {
		std::cout << isColliding << " this collider status " << std::endl;

		/*gameObject->setIsActive(false);
		isColliding = false;
		ShowCaseScene::EnqueueEnemy(gameObject);*/
	}
	void OnCollisionExit(GameObject& other) override {
		std::cout << isColliding << " this collider status " << std::endl;
	}
};
std::queue<GameObject*> ShowCaseScene::bulletPool;
std::queue<GameObject*> ShowCaseScene::enemyPool;

std::string ShowCaseScene::getName() const {
	return "ShowCaseScene";
}

void ShowCaseScene::initialize() {
	player = new GameObject("Player", Player);
	player->addComponent<SpriteRenderer>("../assets/player.png", Vector4(0.0f, 255.0f, 0.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.1f, 0.1f));
	player->addComponent<CircleCollider>(15.0f, true);


	go1 = new GameObject("Fumo", Enemy);
	go1->addComponent<SpriteRenderer>("../assets/fumo.png", Vector4(255.0f, 255.0f, 255.0f, 0.8f));
	go1->addComponent<EnemyCollider>(35.0f, true);
	go1->getComponent<EnemyCollider>()->addCollidableTag(Player);
	go1->getComponent<EnemyCollider>()->addCollidableTag(Bullet);
	go1->transform->setXPosition(-300.0f);

	ShowCaseScene::EnqueueEnemy(go1);


	for (int x = 0; x < 10; x++)
	{
		GameObject* newEnemy = new GameObject("Fumo", Enemy);
		newEnemy->addComponent<SpriteRenderer>("../assets/fumo.png");
		newEnemy->addComponent<EnemyCollider>(35.0f, true);
		newEnemy->getComponent<EnemyCollider>()->addCollidableTag(Player);
		newEnemy->getComponent<EnemyCollider>()->addCollidableTag(Bullet);
		newEnemy->setIsActive(false);

		ShowCaseScene::EnqueueEnemy(newEnemy);
	}

	for (int x = 0; x < 15; x++)
	{
		GameObject* newBullet = new GameObject("Bullet", Bullet);
		newBullet->addComponent<RendererComponent>(Circle);
		newBullet->addComponent<CircleCollider>(10.0f);
		newBullet->setIsActive(false);
		ShowCaseScene::EnqueueBullet(newBullet);
	}
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {
	if (player)
	{
		float angleInDegrees = std::atan2(Input::getMousePositionCentered().y - player->transform->getYPosition(),
			Input::getMousePositionCentered().x - player->transform->getXPosition()) * (180.0f / M_PI);

		player->transform->setRotation(angleInDegrees - 90.0f);
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

	if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_1))
	{
		GameObject* bullet = DequeueBullet(); // Get a bullet from the pool
		if (bullet)
		{
			bullet->transform->setPosition(player->transform->getPosition());
			bullet->setIsActive(true);

			/*Vector2 testD(Input::getMousePositionCentered().y - player->transform->getYPosition(),
				Input::getMousePositionCentered().x - player->transform->getXPosition()
			);*/
			Vector2 direction(
				cos((player->transform->getRotation() + 90.0f) * (M_PI / 180.0f)),
				sin((player->transform->getRotation() + 90.0f) * (M_PI / 180.0f))
			);
			direction = Vector2::normalize(direction);

			bullet->transform->setVelocity(Vector2(direction.x * 150.0f, direction.y * 150.0f));
		}
	}

	if (Input::getKeyDown(GLFW_KEY_Q))
	{
		player->setIsActive(!player->getIsActive());
	}
}

void ShowCaseScene::EnqueueBullet(GameObject* obj)
{
	bulletPool.push(obj);
}

GameObject* ShowCaseScene::DequeueBullet()
{
	if (bulletPool.empty()) return nullptr;
	GameObject* deqObj = bulletPool.front();
	bulletPool.pop();

	return deqObj;
}

void ShowCaseScene::EnqueueEnemy(GameObject* obj)
{
	enemyPool.push(obj);
}

GameObject* ShowCaseScene::DequeueEnemy()
{
	if (enemyPool.empty()) return nullptr;
	GameObject* deqObj = enemyPool.front();
	enemyPool.pop();

	return deqObj;
}

void ShowCaseScene::DebugSize()
{
	std::cout << "Bullet pool current size: " << bulletPool.size() << std::endl;
	std::cout << "Enemy pool current size: " << enemyPool.size() << std::endl;
}

