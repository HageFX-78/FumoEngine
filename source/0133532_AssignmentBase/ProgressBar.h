#pragma once

#include <iostream>
#include <glad/glad.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace FumoEngine
{
	/// <summary>
	/// An enum to determine where the progress bar would extrude from
	/// </summary>
	enum BarPivot
	{
		Top,
		Bottom,
		Left,
		Right,
		CenterHorizontal,
		CenterVertical
	};
	/// <summary>
	/// A UI game object that is meant to visualize a progress bar/loading bar, can set which direction the bar extrudes from
	/// </summary>
	class ProgressBar : public BaseComponent
	{
	public:
		ProgressBar(GameObject* go, BarPivot defaultPivot = Left, float brLength = 500.0f, float brHeight = 30.0f, float prog = 0.5f);
		~ProgressBar();
		void update(float deltaTime) override;
		void render() override;

		void setBackDropColor(float r, float g, float b, float a);
		Vector4 getBackDropColor();

		void setBarColor(float r, float g, float b, float a);
		Vector4 getBarColor();

		void setBothBarOpacity(float a);

		void setPivot(float x, float y);
		void setBarExtrudeFrom(BarPivot value);

		void setProgress(float value);
		float getProgress();

		void setBarLength(float value);
		float getBarLength();
		void setBarHeight(float value);
		float getBarHeight();

		
	protected:
		//colors
		Vector4 progressBarColor;
		Vector4 progressBarBackgroundColor;

		/// <summary>
		/// Bar length and height for both the top and bottom bar of the progress bar
		/// </summary>
		float barLength;
		float barHeight;

		float progress;
		/// <summary>
		/// Where the bar extrudes from, Left is the default.<br>
		/// In this state, adding the progress value of the bar would extend the bar from left to right.
		/// </summary>
		BarPivot extrudeFrom;

		TransformComponent* localTransform;

		/// <summary>
		/// Pivot point similar to spriteRenderer
		/// </summary>
		Vector3 pivotPoint;

		/// <summary>
		/// Function to draw both progress bar with given length and height
		/// </summary>
		/// <param name="length"></param>
		/// <param name="height"></param>
		void drawProgressBar(float length, float height);//Current values, can be swapped

		/// <summary>
		/// Somewhat private Function to simplify the process of drawing the innerbar extruding from diffent directions
		/// </summary>
		/// <param name="left"></param>
		/// <param name="top"></param>
		/// <param name="right"></param>
		/// <param name="bottom"></param>
		/// <param name="color"></param>
		void DrawQuad(float left, float top, float right, float bottom, const Vector4& color);
	};
}


