#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* go) : BaseComponent(go) {
	allowMultiple = false;//Set to not be possible to be added multiple times

}
TransformComponent::~TransformComponent() {
}

void TransformComponent::update(float deltaTime)
{
	xPosition += velocity.x * deltaTime;
	yPosition += velocity.y * deltaTime;
}

// Current Component Functions
#pragma region This Component Functions

void TransformComponent::setXPosition(float value)
{
	xPosition = value;
}
void TransformComponent::setYPosition(float value)
{
	yPosition = value;
}
void TransformComponent::setPosition(float x, float y)
{
	xPosition = x;
	yPosition = y;
}
void TransformComponent::setPosition(Vector2 value)
{
	xPosition = value.x;
	yPosition = value.y;
}
float TransformComponent::getXPosition() const
{
	return xPosition;
}
float TransformComponent::getYPosition() const
{
	return yPosition;
}
Vector2 TransformComponent::getPosition() const
{
	return Vector2(xPosition, yPosition);
}



void TransformComponent::setXScale(float value)
{
	xScale = value;
}
void TransformComponent::setYScale(float value)
{
	yScale = value;
}
void TransformComponent::setScale(float x, float y)
{
	xScale = x;
	yScale = y;
}
void TransformComponent::setScale(Vector2 value)
{
	xScale = value.x;
	yScale = value.y;
}
float TransformComponent::getXScale() const
{
	return xScale;
}
float TransformComponent::getYScale() const
{
	return yScale;
}

Vector2 TransformComponent::getScale() const
{
	return Vector2(xScale, yScale);
}



void TransformComponent::setRotation(float value)
{
	rotation = value;
}
float TransformComponent::getRotation() const
{
	return rotation;
}



void TransformComponent::setVelocity(Vector2 value)
{
	velocity = value;
}
Vector2 TransformComponent::getVelocity() const
{
	return velocity;
}

#pragma endregion


