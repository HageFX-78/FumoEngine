#pragma once

#include <iostream>
#include "GameObject.h"
#include "BaseComponent.h"
#include <glad/glad.h>
#include "TransformComponent.h"

enum ShapeToDraw
{
	Quad,
	Triangle
};

class RendererComponent : public BaseComponent
{
public:
	RendererComponent(GameObject* go);
	~RendererComponent();
	void awake() override;
	void start() override;
	void update(float deltaTime) override;
	void render() override;

	void setRGB(float r, float g, float b);
	void getRGB();

	void setShapeToDraw(ShapeToDraw value);

protected:
	float r, g, b;
	TransformComponent* localTransform;
	float anchorOffsetX, anchorOffsetY;
	ShapeToDraw defaultShape = Quad;

	void drawQuad();
	void drawTriangle();
};

