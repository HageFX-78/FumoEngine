#define _USE_MATH_DEFINES
#include <cmath>

#include "CircleCollider.h"
#include "GameObjectCollection.h"

namespace FumoEngine
{
	CircleCollider::CircleCollider(GameObject* go, float rad, bool isVisible) : BaseComponent(go), radius(rad), showCollider(isVisible)
	{
		localTransform = go->transform;
	}

	CircleCollider::~CircleCollider()
	{
	}

	void CircleCollider::update(float deltaTime)
	{
		if (!isColliding && !collidedCache.empty()) collidedCache.clear();//Clear cache if leftover from before

		std::unordered_set<GameObject*> currentCollidingObjects;

		for (GameObject* sceneObj : GameObjectCollection::getCurrentSceneGameObjects())
		{
			if (sceneObj == gameObject || !sceneObj->getIsActive() || !sceneObj->getComponent<CircleCollider>()) continue;

			for (UserTag tag : collidables)
			{
				if (sceneObj->getTag() != tag) continue;

				bool isInCircle = checkCircleCollision(*sceneObj->getComponent<CircleCollider>());
				if (isInCircle)
				{
					if (!isColliding)
					{
						isColliding = true;
						collidedCache.insert(sceneObj);
						OnCollisionEnter(*sceneObj);
					}
				}
			}
		}

		for (GameObject* cc : collidedCache)
		{
			bool isInCircle = checkCircleCollision(*cc->getComponent<CircleCollider>());
			if (isInCircle)
			{

				OnCollisionStay(*cc);
				currentCollidingObjects.insert(cc); //Latest collided objects list
			}
			else
			{
				isColliding = false;
				OnCollisionExit(*cc);
			}
		}

		collidedCache = currentCollidingObjects;
	}

	void CircleCollider::render()
	{
		if (showCollider)
		{
			glPushMatrix();

			// Translation
			Vector3 translationVector(localTransform->getXPosition(), localTransform->getYPosition(), 0.0f);
			Matrix4 translationMatrix = Matrix4::translate(translationVector);

			// Rotation
			float angleDegrees = localTransform->getRotation();
			Matrix4 rotationMatrix = Matrix4::rotate(angleDegrees, Vector3(0.0f, 0.0f, 1.0f));


			// Scale
			Vector3 scaleVector(localTransform->getXScale(), localTransform->getYScale(), 1.0f);
			Matrix4 scaleMatrix = Matrix4::scale(scaleVector);


			Matrix4 allMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			glMultMatrixf(allMatrix.data);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


			float faceAngle = (360 / abs(12)) * (M_PI / 180);

			glBegin(GL_TRIANGLE_STRIP);
			glColor4f(102.0f / 255.0f, 1.0f, 46.0f / 255.0f, 0.5f);
			for (int x = 0; x <= 12; x++)
			{
				glVertex3f(radius * sin(faceAngle * x), radius * cos(faceAngle * x), 0.0f);
				glVertex3f(0 * sin(faceAngle * x), 0 * cos(faceAngle * x), 0.0f);
			}
			glEnd();


			glDisable(GL_BLEND);

			glPopMatrix();
		}
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

	void CircleCollider::addCollidableTag(UserTag tag)
	{
		collidables.insert(tag);
	}

	void CircleCollider::removeCollidableTag(UserTag tag)
	{
		collidables.erase(tag);
	}

	std::unordered_set<UserTag> CircleCollider::getCollidableTags()
	{
		return collidables;
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

	void CircleCollider::OnCollisionEnter(GameObject& other) {}

	void CircleCollider::OnCollisionExit(GameObject& other) {}

	void CircleCollider::OnCollisionStay(GameObject& other) {}
}






