#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace FumoEngine
{
	class Texture;
	/// <summary>
	/// A component to add simple 2D sprites and attach them to game objects.
	/// </summary>
	class SpriteRenderer : public BaseComponent
	{
	public:
		SpriteRenderer(GameObject* go,
			std::string spritePath = "../assets/fumoEngine.png",
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

		/// <summary>
		/// Defines the width and height scale locally of said texture. It is essentially a second layer of scaling
		/// used only on the texture of this specific game object. So different textures may have different sprite sizes without affecting
		/// the scale on transform component.
		/// </summary>
		float w, h;

		/// <summary>
		/// Pivot point, it is in Vector3 because the provided Matrix library only accepts Vector3, it is done for convenience sake.<br>
		/// Getting and setting the value is done in Vector2 so it does not affect the user.
		/// </summary>
		Vector3 pivotPoint;//So i can easily add it to matrix4
	};
}


