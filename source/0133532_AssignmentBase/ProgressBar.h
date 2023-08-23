#pragma once

#include <iostream>
#include "GameObject.h"
#include "BaseComponent.h"
#include <glad/glad.h>
#include "TransformComponent.h"

class ProgressBar : public BaseComponent
{
public:
	ProgressBar(GameObject* go);
	~ProgressBar();
	void update(float deltaTime) override;
	void render() override;

	void setBackDropColor(float r, float g, float b);
	void getBackDropColor();

	void setBarColor(float r, float g, float b);
	void getBarColor();

protected:
	float pR, pG, pB;
	float bR, bG, bB;
	TransformComponent* localTransform;
	void drawBackDrop();
	void drawProgressBar();
};

