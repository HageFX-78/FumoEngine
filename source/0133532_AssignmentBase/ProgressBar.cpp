#include "ProgressBar.h"
#include "TransformComponent.h"

ProgressBar::ProgressBar(GameObject* go, float brLen, float brHei, float prog) : BaseComponent(go), barLength(brLen), barHeight(brHei), progress(prog)
{
	allowMultiple = false;

	setBackDropColor(0.0, 0.0f, 0.0f, 1.0f);
	setBarColor(255.0f, 255.0f, 255.0f, 1.0f);

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

void ProgressBar::getBackDropColor()
{
}

void ProgressBar::setBarColor(float r, float g, float b, float a)
{
	progressBarColor = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a);
}

void ProgressBar::getBarColor()
{
}

void ProgressBar::setPivot(float x, float y)
{
	pivotPoint = Vector3(x, y, 0.0f);
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
	Matrix4 pivotTranslate = Matrix4::translate(pivotPoint);
	Matrix4 pivotRotate = Matrix4::rotate(localTransform->getRotation(), Vector3(0.0f, 0.0f, 1.0f));
	Matrix4 pivotTranslateBack = Matrix4::translate(-pivotPoint);
	Matrix4 rotationMatrix = pivotTranslate * pivotRotate * pivotTranslateBack;//Apply pivot rotation on pivot point before reverting back to normal

	// Scale
	Vector3 scaleVector(localTransform->getXScale(), localTransform->getYScale(), 1.0f);
	Matrix4 scaleMatrix = Matrix4::scale(scaleVector);

	Matrix4 allMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	glMultMatrixf(allMatrix.data);

	float innerBarWidth = length * progress;

	glBegin(GL_QUADS);
	glColor3f(progressBarBackgroundColor.x, progressBarBackgroundColor.y, progressBarBackgroundColor.z);
	glVertex3f(-length / 2, height / 2, 0.0f);
	glVertex3f(-length / 2, -height / 2, 0.0f);
	glVertex3f(length / 2, -height / 2, 0.0f);
	glVertex3f(length / 2, height / 2, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(progressBarColor.x, progressBarColor.y, progressBarColor.z);
	glVertex3f(-length / 2 , height / 2, 0.0f);
	glVertex3f(-length / 2, -height / 2, 0.0f);
	glVertex3f(-length / 2 + innerBarWidth, -height / 2, 0.0f);
	glVertex3f(-length / 2 + innerBarWidth, height / 2, 0.0f);
	glEnd();

	glPopMatrix();
}

