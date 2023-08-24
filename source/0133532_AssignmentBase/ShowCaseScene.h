#pragma once
#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>
#include <string>
class ShowCaseScene : public BaseScene {
public:
	std::string getName() const override;

protected:
	void initialize() override;
	void on_activate() override;
	void on_update(float deltaTime) override;

private:
	GameObject* go1;
	GameObject* go2;
	GameObject* player;

	GameObject* progressbar;
	float testVal = 0;
};

