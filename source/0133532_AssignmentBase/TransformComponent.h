#pragma once

#include <iostream>
#include "GameObject.h"
#include "BaseComponent.h"

enum Anchor {
	center,
	left,
	right,
	top,
	bottom
};

class TransformComponent : public BaseComponent
{
public:
	TransformComponent(GameObject* go);
	~TransformComponent();

	void setXPosition(float value);
	void setYPosition(float value);
	float getXPosition() const;
	float getYPosition() const;

	void setXScale(float value);
	void setYScale(float value);
	float getXScale() const;
	float getYScale() const;

	void setRotation(float value);
	float getRotation() const;

	void setAnchorPosition(Anchor value);
	Anchor getAnchorPosition() const;

	
protected:
	float xPosition = 0, yPosition = 0, xScale = 1, yScale = 1, rotation = 0;
	Anchor anchor = center;
};

