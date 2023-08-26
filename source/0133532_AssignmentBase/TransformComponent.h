#pragma once

#include <iostream>
#include "angle_util/vector.h"

#include "GameObject.h"
#include "BaseComponent.h"

namespace FumoEngine
{
	/// <summary>
	/// A core component that is added to every game object by default, governs the position, scale and orientation of game objects.
	/// </summary>
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject* go);
		~TransformComponent();

		void update(float deltaTime) override;

		void setXPosition(float value);
		void setYPosition(float value);
		void setPosition(float x, float y);
		void setPosition(Vector2 value);

		float getXPosition() const;
		float getYPosition() const;
		Vector2 getPosition() const;

		void setXScale(float value);
		void setYScale(float value);
		void setScale(float x, float y);
		void setScale(Vector2 value);

		float getXScale() const;
		float getYScale() const;
		Vector2 getScale() const;

		void setRotation(float value);
		float getRotation() const;

		void setVelocity(Vector2 value);
		Vector2 getVelocity() const;

	protected:
		float xPosition = 0, yPosition = 0, xScale = 1, yScale = 1, rotation = 0;

		/// <summary>
		/// Velocity of actor, an alternative to setting position manually for movement.
		/// It is used to set a constant velocity with indefinite period of time
		/// </summary>
		Vector2 velocity;
	};
}


