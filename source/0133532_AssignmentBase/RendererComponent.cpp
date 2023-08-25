#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "RendererComponent.h"
#include "TransformComponent.h"
#include "angle_util/matrix.h"
#include "angle_util/vector.h"


RendererComponent::RendererComponent(GameObject* go, ShapeToDraw defShape) : BaseComponent(go), defaultShape(defShape) {
	allowMultiple = false;
	setRGB(255.0f, 255.0f, 255.0f);
	localTransform = gameObject->transform;

	std::cout << "<@> Created Renderer Component on " << gameObject->getName() << std::endl;
}
RendererComponent::~RendererComponent() {
	std::cout << "<!> Renderer component of " << gameObject->getName() << " is destroyed" << std::endl;
}

void RendererComponent::update(float deltaTime)
{
}

void RendererComponent::render()
{
	if (!gameObject->getIsActive()) return;

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


	switch (defaultShape) {
	case Quad:
		drawQuad();
		break;
	case Triangle:
		drawTriangle();
		break;
	case Circle:
		drawCircle(circlePartition, circleRadius);
		break;
	}


	glPopMatrix();
}

// Current Component Functions
#pragma region This Component Functions

void RendererComponent::setRGB(float nR, float nG, float nB)
{
	r = nR / 255.0f;
	g = nG / 255.0f;
	b = nB / 255.0f;
}
void RendererComponent::getRGB()
{
	std::cout << "R : " << r << ", G : " << g << ", B : " << b << std::endl;
}

void RendererComponent::setCircleDrawValues(int circlePartition, float circleRadius)
{
	this->circlePartition = circlePartition;
	this->circleRadius = circleRadius;
}

void RendererComponent::setShapeToDraw(ShapeToDraw value)
{
	defaultShape = value;
}

void RendererComponent::drawQuad()
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(-50, 50, 0.0f);//Change to 100 following the change to 1 pixel unit
	glVertex3f(-50, -50, 0.0f);
	glVertex3f(50, -50, 0.0f);
	glVertex3f(50, 50, 0.0f);
	glEnd();
}

void RendererComponent::drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(r, g, b);
	glVertex3f(0, 50, 0);
	glVertex3f(-50, -50, 0);
	glVertex3f(50, -50, 0);
	glEnd();
}
void RendererComponent::drawCircle(int faceCount, float radius)
{
	float faceAngle = (360 / abs(faceCount)) * (M_PI / 180);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int x = 0; x <= faceCount; x++)
	{
		glVertex3f(radius * sin(faceAngle * x), radius * cos(faceAngle * x), 0.0f);
		glVertex3f(0 * sin(faceAngle * x), 0 * cos(faceAngle * x), 0.0f);
	}
	glEnd();

}
#pragma endregion


