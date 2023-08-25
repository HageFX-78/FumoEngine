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
	EnemyCollider(GameObject* go, int& plives, float rad = 30.0f, bool isVisible = false) : CircleCollider(go, rad, isVisible), playerLives(plives) {
	}

	void OnCollisionEnter(GameObject& other) override {
		std::cout << "Collided object name : " << other.getName() << std::endl;
	}

private:
	int& playerLives;
};

std::string ShowCaseScene::getName() const {
	return "ShowCaseScene";
}

void ShowCaseScene::initialize() {
	player = new GameObject("Player", Player);
	player->addComponent<SpriteRenderer>("../assets/player.png", Vector4(0.0f, 255.0f, 0.0f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.1f, 0.1f));
	player->addComponent<CircleCollider>(15.0f, true);


	go1 = new GameObject("Fumo", Enemy);
	go1->addComponent<SpriteRenderer>("../assets/fumo.png", Vector4(255.0f, 255.0f, 255.0f, 0.8f));
	go1->addComponent<EnemyCollider>(playerLives, 30.0f, true);
	go1->getComponent<EnemyCollider>()->addCollidableTag(Player);
	go1->getComponent<EnemyCollider>()->addCollidableTag(Bullet);
	go1->transform->setXPosition(-300.0f);


	/*for (int x = 0; x < 10; x++)
	{
		GameObject* newBullet = new GameObject();
		newBullet->addComponent<SpriteRenderer>();
		newBullet->addComponent<CircleCollider>(10.0f);
		bulletPool.push(newBullet);
	}*/
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {
	if (player)
	{
		float angleInDegrees = std::atan2(Input::getMousePositionCentered().y - player->transform->getYPosition(),
			Input::getMousePositionCentered().x - player->transform->getXPosition()) * (180.0f / M_PI);

		player->transform->setRotation(angleInDegrees - 90);
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

	}

	if (Input::getKeyDown(GLFW_KEY_Q))
	{
		player->setIsActive(!player->getIsActive());
	}
	if (Input::getKeyDown(GLFW_KEY_E))
	{
		std::cout << goPool.size() << std::endl;

		for (GameObject* gob : goPool)
		{
			std::cout << gob->getIsActive() << std::endl;
		}
	}


	
}

