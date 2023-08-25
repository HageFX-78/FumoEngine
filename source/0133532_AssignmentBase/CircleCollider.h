#pragma once

#include <unordered_set>
#include <glad/glad.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "BaseComponent.h"
#include "TransformComponent.h"

class CircleCollider : public BaseComponent
{
public:
	CircleCollider(GameObject* go,  float rad = 5.0f, bool isVisible = false);
	~CircleCollider();
	void update(float deltaTime) override;
	void render() override;

	void setRadius(float rad);
	float getRadius() const;

	Vector2 getCenter() const;

	void addCollidableTag(UserTag typeName);
	void removeCollidableTag(UserTag typeName);
	std::unordered_set<UserTag> getCollidableTags();

	void setIsColliding(bool value);
	bool getIsColliding() const;

	bool containsPoint(const Vector2& point) const;
	bool checkCircleCollision(const CircleCollider& other);
	
	virtual void OnCollisionEnter(GameObject& other);
	virtual void OnCollisionExit(GameObject& other);
	virtual void OnCollisionStay(GameObject& other);

protected:
	std::unordered_set<UserTag> collidables = {Default};

	TransformComponent* localTransform;
	float radius;
	
	bool isColliding = false;
	bool showCollider = false;

};

