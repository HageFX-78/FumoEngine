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
	int playerLives = 3;
protected:
	void initialize() override;
	void on_activate() override;
	void on_update(float deltaTime) override;


	void SceneCollisionCheck();

	
private:
	

	GameObject* go1;
	GameObject* player;

	std::vector<GameObject*> goPool;//ALl objects in the scene
	std::queue<GameObject*> bulletPool;
	std::queue<GameObject*> enemyPool;
};

