#pragma once
#include <glad/glad.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "BaseComponent.h"
#include "TransformComponent.h"

class CircleCollider : public BaseComponent
{
public:
	CircleCollider(GameObject* go, bool isVisible = false, float rad = 5.0f);
	~CircleCollider();
	void update(float deltaTime) override;
	void render() override;

	void setRadius(float rad);
	float getRadius() const;

	Vector2 getCenter() const;

	void setIsColliding(bool value);
	bool getIsColliding() const;

	bool containsPoint(const Vector2& point) const;
	bool checkCircleCollision(const CircleCollider& other);
	
	
protected:
	//Vector2 vector2Diff(Vector2 v1, Vector2 v2);//Find diff

	TransformComponent* localTransform;
	float radius;
	
	bool isColliding = false;
	bool showCollider = false;

};

