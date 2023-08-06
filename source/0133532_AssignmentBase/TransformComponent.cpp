#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* go) : BaseComponent(go) {
	allowMultiple = false;//Set to not be possible to be added multiple times

	std::cout << "<@> Created Transform Component on " << gameObject->getName() << std::endl;
}
TransformComponent::~TransformComponent() {
	std::cout << "<!> Transform component of " << gameObject->getName() << " is destroyed" << std::endl;
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
void TransformComponent::setXScale(float value)
{
	xScale = value;
}
void TransformComponent::setYScale(float value)
{
	yScale = value;
}
void TransformComponent::setRotation(float value)
{
	rotation = value;
}


float TransformComponent::getXPosition() const
{
	return xPosition;
}

float TransformComponent::getYPosition() const
{
	return yPosition;
}
float TransformComponent::getXScale() const
{
	return xScale;
}
float TransformComponent::getYScale() const
{
	return yScale;
}

float TransformComponent::getRotation() const
{
	return rotation;
}
void TransformComponent::setAnchorPosition(Anchor value)
{
	anchor = value;
}
Anchor TransformComponent::getAnchorPosition() const
{
	return anchor;
}
#pragma endregion


