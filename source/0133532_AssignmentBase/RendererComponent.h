#pragma once

#include <iostream>
#include <glad/glad.h>

#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"



enum ShapeToDraw
{
	Quad,
	Triangle,
	Circle
};

class RendererComponent : public BaseComponent
{
public:
	RendererComponent(GameObject* go, ShapeToDraw defShape = Quad);
	~RendererComponent();
	void update(float deltaTime) override;
	void render() override;

	void setRGB(float r, float g, float b);
	Vector3 getRGB();

	void setCircleDrawValues(int circlePartition, float circleRadius);

	void setShapeToDraw(ShapeToDraw value);

protected:
	float r, g, b;
	TransformComponent* localTransform;
	ShapeToDraw defaultShape;

	int circlePartition = 5;
	float circleRadius = 5.0f;

	void drawQuad();
	void drawTriangle();
	void drawCircle(int faceCount, float radius);
};

