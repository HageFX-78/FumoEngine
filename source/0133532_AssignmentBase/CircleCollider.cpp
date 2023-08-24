#include "CircleCollider.h"
#include <cmath>

CircleCollider::CircleCollider(GameObject* go, bool isVisible, float rad) : BaseComponent(go), showCollider(isVisible), radius(rad)
{
	localTransform = go->transform;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::update(float deltaTime)
{

}

void CircleCollider::render()
{
}
void CircleCollider::setRadius(float rad)
{
	this->radius = rad;
}
float CircleCollider::getRadius() const
{
	return radius;
}

Vector2 CircleCollider::getCenter() const
{
	return Vector2(localTransform->getXPosition(), localTransform->getYPosition());
}

void CircleCollider::setIsColliding(bool value)
{
	isColliding = value;
}

bool CircleCollider::getIsColliding() const
{
	return isColliding;
}



//Local function to calculate length between 2 vector2, as the original only provide for Vector3
Vector2 vector2Diff(Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

bool CircleCollider::containsPoint(const Vector2& point) const
{
	Vector2 center = Vector2(localTransform->getXPosition(), localTransform->getYPosition()); // Assuming TransformComponent
	float squaredDistance = Vector2::lengthSquared(vector2Diff(center, point));

	return squaredDistance <= (radius * radius);
}

bool CircleCollider::checkCircleCollision(const CircleCollider& other)
{
	Vector2 centerDiff = vector2Diff(other.getCenter(), this->getCenter());
	float squaredDistance = Vector2::lengthSquared(centerDiff);

	float squaredRadSum = std::pow(this->getRadius() + other.getRadius(), 2);

	return squaredDistance <= squaredRadSum;
}





