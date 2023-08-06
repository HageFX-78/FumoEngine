#pragma once

#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>

#include "angle_util/matrix.h"
#include "angle_util/vector.h"

class SplashScene : public BaseScene {
public:
	std::string getName() const override;

protected:
	void initialize() override;
	void on_activate() override;
	void on_update(float deltaTime) override;
	void on_render() override;

	float time;
	float sceneSwitchTime = 10.0f;
private:
	GameObject* go1;
	GameObject* go2;
};

