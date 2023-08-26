#include "ProgressBar.h"
#include "TransformComponent.h"

namespace FumoEngine
{
	ProgressBar::ProgressBar(GameObject* go, BarPivot defaultPivot, float brLen, float brHei, float prog)
		: BaseComponent(go), extrudeFrom(defaultPivot), barLength(brLen), barHeight(brHei), progress(prog)
	{
		allowMultiple = false;

		setBackDropColor(0.0, 0.0f, 0.0f, 1.0f);
		setBarColor(255.0f, 255.0f, 255.0f, 1.0f);
		setPivot(0.0f, 0.5f);

		localTransform = go->transform;
	}

	ProgressBar::~ProgressBar()
	{
	}
	void ProgressBar::update(float deltaTime) {}

	void ProgressBar::render()
	{
		drawProgressBar(barLength, barHeight);
	}

	void ProgressBar::setBackDropColor(float r, float g, float b, float a)
	{
		progressBarBackgroundColor = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a);

	}

	Vector4 ProgressBar::getBackDropColor()
	{
		return progressBarBackgroundColor;
	}

	void ProgressBar::setBarColor(float r, float g, float b, float a)
	{
		progressBarColor = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a);
	}

	Vector4 ProgressBar::getBarColor()
	{
		return progressBarColor;
	}

	void ProgressBar::setBothBarOpacity(float a)
	{
		progressBarBackgroundColor.w = a;
		progressBarColor.w = a;
	}

	void ProgressBar::setPivot(float x, float y)
	{
		pivotPoint = Vector3(x, y, 0.0f);
	}

	void ProgressBar::setBarExtrudeFrom(BarPivot value)
	{
		extrudeFrom = value;
	}


	void ProgressBar::setProgress(float value)
	{
		progress = std::max(0.0f, std::min(value, 1.0f));
	}

	float ProgressBar::getProgress()
	{
		return progress;
	}

	float ProgressBar::getBarLength()
	{
		return barLength;
	}

	void ProgressBar::drawProgressBar(float length, float height)
	{
		glPushMatrix();

		// Translation
		Vector3 translationVector(localTransform->getXPosition(), localTransform->getYPosition(), 0.0f);
		Matrix4 translationMatrix = Matrix4::translate(translationVector);

		// Rotation
		float pivotX = 2.0f * pivotPoint.x - 1.0f;//Scale the default -1.0 to 1.0 pivot till 0.0 to 1,0 based on requirement
		float pivotY = 2.0f * pivotPoint.y - 1.0f;
		Vector3 pivotOffset(pivotX * length * 0.5f, pivotY * height * 0.5f, 0.0f);

		Matrix4 pivotTranslate = Matrix4::translate(pivotOffset);
		Matrix4 pivotRotate = Matrix4::rotate(localTransform->getRotation(), Vector3(0.0f, 0.0f, 1.0f));
		Matrix4 pivotTranslateBack = Matrix4::translate(-pivotOffset);
		Matrix4 rotationMatrix = pivotTranslate * pivotRotate * pivotTranslateBack;//Apply pivot rotation on pivot point before reverting back to normal

		// Scale
		Vector3 scaleVector(localTransform->getXScale(), localTransform->getYScale(), 1.0f);
		Matrix4 scaleMatrix = Matrix4::scale(scaleVector);

		Matrix4 allMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		glMultMatrixf(allMatrix.data);

		DrawQuad(-length / 2, height / 2, length / 2, -height / 2, progressBarBackgroundColor);

		// Draw progress bar
		float innerBarWidth = length * progress;
		float innerBarHeight = height * progress;
		switch (extrudeFrom)
		{
		case Left:
			DrawQuad(-length / 2, height / 2, -length / 2 + innerBarWidth, -height / 2, progressBarColor);
			break;
		case Right:
			DrawQuad(length / 2 - innerBarWidth, height / 2, length / 2, -height / 2, progressBarColor);
			break;
		case Top:
			DrawQuad(-length / 2, height / 2, length / 2, height / 2 - innerBarHeight, progressBarColor);
			break;
		case Bottom:
			DrawQuad(-length / 2, -height / 2 + innerBarHeight, length / 2, -height / 2, progressBarColor);
			break;
		case CenterHorizontal:
			DrawQuad(0 - innerBarWidth / 2, height / 2, 0 + innerBarWidth / 2, -height / 2, progressBarColor);
			break;
		case CenterVertical:
			DrawQuad(-length / 2, 0 + innerBarHeight /2  , length / 2, 0 - innerBarHeight / 2, progressBarColor);
			break;

		}
		glPopMatrix();
	}

	void ProgressBar::DrawQuad(float left, float top, float right, float bottom, const Vector4& color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBegin(GL_QUADS);
		glColor4f(color.x, color.y, color.z, color.w);
		glVertex3f(left, top, 0.0f);
		glVertex3f(left, bottom, 0.0f);
		glVertex3f(right, bottom, 0.0f);
		glVertex3f(right, top, 0.0f);
		glEnd();

		glDisable(GL_BLEND);
	}
}


