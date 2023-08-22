#pragma once
#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>
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
	float testVal = 0;
};

