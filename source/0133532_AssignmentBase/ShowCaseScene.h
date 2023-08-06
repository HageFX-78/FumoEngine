#pragma once
#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>

#include "GameObject.h";

class ShowCaseScene : public BaseScene {
public:
	std::string getName() const override;

protected:
	void initialize() override;
	void on_activate() override;
	void on_update(float deltaTime) override;

private:
	
};

