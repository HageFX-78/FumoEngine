#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

class Texture;
class SpriteRenderer : public BaseComponent
{
public:
	SpriteRenderer(GameObject* go, 
		std::string spritePath = "../assets/herta.png",
		Vector4 dColor = Vector4(255.0f, 255.0f, 255.0f, 1.0f),
		Vector2 dPivot = Vector2(0.5f, 0.5f),
		Vector2 dSize = Vector2(1.0f, 1.0f));
	~SpriteRenderer();

	void render() override;

	void setColor(float r, float g, float b);
	void setColor(Vector3 color);
	Vector3 getColor();

	void setOpacity(float a);
	float getOpacity();

	void setSize(float w, float h);
	void setSize(Vector2 size);
	Vector2 getSize();

	void setPivot(float x, float y);
	void setPivot(Vector2 pivot);
	Vector2 getPivot();

	void setSprite(std::string path);
protected:
	TransformComponent* localTransform;
	Texture* texture;

	float r, g, b, a;
	float w, h;
	
	Vector3 pivotPoint;//So i can easily add it to matrix4
};

