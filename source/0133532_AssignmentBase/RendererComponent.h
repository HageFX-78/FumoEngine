#pragma once

#include <iostream>
#include <glad/glad.h>

#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"


namespace FumoEngine
{
	/// <summary>
	/// Predefined primitive shapes to draw
	/// </summary>
	enum ShapeToDraw
	{
		Quad,
		Triangle,
		Circle
	};

	/// <summary>
	/// Depreceated renderer component that is used to render primitive shapes like Quad, Triangle and Circle<br>
	/// Only circle radius and partition can be given values, the other shapes are rendered based on engine default.
	/// </summary>
	class RendererComponent : public BaseComponent
	{
	public:
		RendererComponent(GameObject* go, ShapeToDraw defShape = Quad);
		~RendererComponent();
		void update(float deltaTime) override;
		void render() override;

		void setRGB(float r, float g, float b);
		Vector3 getRGB();

		void setCircleDrawValues(int circlePartition, float circleRadius);

		void setShapeToDraw(ShapeToDraw value);

	protected:
		float r, g, b;
		TransformComponent* localTransform;
		ShapeToDraw defaultShape;

		int circlePartition = 5;
		float circleRadius = 5.0f;

		void drawQuad();
		void drawTriangle();
		void drawCircle(int faceCount, float radius);
	};
}


