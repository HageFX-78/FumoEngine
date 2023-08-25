#pragma once

#include <iostream>
#include <glad/glad.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

class ProgressBar : public BaseComponent
{
public:
	ProgressBar(GameObject* go, float brLength = 500.0f, float brHeight = 30.0f, float prog = 0.5f);
	~ProgressBar();
	void update(float deltaTime) override;
	void render() override;

	void setBackDropColor(float r, float g, float b, float a);
	Vector4 getBackDropColor();

	void setBarColor(float r, float g, float b, float a);
	Vector4 getBarColor();

	void setBothBarOpacity(float a);

	void setPivot(float x, float y);

	void setProgress(float value);
	float getProgress();

	float getBarLength();
protected:
	//colors
	Vector4 progressBarColor;
	Vector4 progressBarBackgroundColor;

	//Default/Max values for length and height
	float barLength;
	float barHeight;

	float progress;

	TransformComponent* localTransform;
	Vector3 pivotPoint;
	void drawProgressBar(float length, float height);//Current values, can be swapped
};

