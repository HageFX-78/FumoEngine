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

	int playerLives = 3;

protected:
	void initialize() override;
	void on_activate() override;
	void on_update(float deltaTime) override;
	
	
private:
	GameObject* go1;
	GameObject* go2;
	GameObject* player;

	static std::queue<GameObject*> bulletPool;
	static std::queue<GameObject*> enemyPool;
};

