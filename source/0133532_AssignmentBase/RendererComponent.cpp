#include "RendererComponent.h"
#include "TransformComponent.h"
#include "angle_util/matrix.h"
#include "angle_util/vector.h"
#include <iostream>

RendererComponent::RendererComponent(GameObject* go) : BaseComponent(go) {
	allowMultiple = false;
	setRGB(255, 255, 255);
	localTransform = gameObject->transform;

	std::cout << "<@> Created Renderer Component on " << gameObject->getName() << std::endl;
}
RendererComponent::~RendererComponent() {
	std::cout << "<!> Renderer component of " << gameObject->getName() << " is destroyed" << std::endl;
}

void RendererComponent::awake()
{

}
void RendererComponent::start()
{
	
}
void RendererComponent::update(float deltaTime)
{
}

void RendererComponent::render()
{
	//Get anchor and set offset, in render to update offset when scale is increased
	Anchor anchorType = localTransform->getAnchorPosition();

	switch (anchorType) {
	case left:
		anchorOffsetX = (localTransform->getXScale() * 100) / 2;//*100 to offset the initial ditance of vertices from opposing sides 
		break;
	case right:
		anchorOffsetX = -(localTransform->getXScale() * 100) / 2;
		break;
	case top:
		anchorOffsetY = (localTransform->getYScale() * 100) / 2;
		break;
	case bottom:
		anchorOffsetY = -(localTransform->getYScale() * 100) / 2;
		break;
	default:
		anchorOffsetX = 0;
		anchorOffsetY = 0;
		break;
	}

	glPushMatrix();

	// Translation
	Vector3 translationVector(localTransform->getXPosition() + anchorOffsetX, localTransform->getYPosition() + anchorOffsetY, 0.0f);
	Matrix4 translationMatrix = Matrix4::translate(translationVector);
	glMultMatrixf(translationMatrix.data);

	// Scale
	Vector3 scaleVector(localTransform->getXScale(), localTransform->getYScale(), 1.0f);
	Matrix4 scaleMatrix = Matrix4::scale(scaleVector);
	glMultMatrixf(scaleMatrix.data);

	// Rotation
	float angleDegrees = localTransform->getRotation();
	Vector3 rotationAxis(0.0f, 0.0f, 1.0f);
	Matrix4 rotationMatrix = Matrix4::rotate(angleDegrees, rotationAxis);
	glMultMatrixf(rotationMatrix.data);


	if (defaultShape == Quad)
	{
		drawQuad();
	}
	else if (defaultShape == Triangle)
	{
		drawTriangle();
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
#pragma endregion


