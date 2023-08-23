#include "ProgressBar.h"
#include "TransformComponent.h"
#include "angle_util/matrix.h"
#include "angle_util/vector.h"

ProgressBar::ProgressBar(GameObject* go) : BaseComponent(go)
{
	allowMultiple = false;
	setBackDropColor(0, 0, 0);
	setBarColor(255.0f, 255.0f, 255.0f);

	localTransform = go->transform;
}

ProgressBar::~ProgressBar()
{
}
void ProgressBar::update(float deltaTime){}

void ProgressBar::render()
{
}

void ProgressBar::setBackDropColor(float r, float g, float b)
{
}

void ProgressBar::getBackDropColor()
{
}

void ProgressBar::setBarColor(float r, float g, float b)
{
}

void ProgressBar::getBarColor()
{
}

void ProgressBar::drawBackDrop()
{
}

void ProgressBar::drawProgressBar()
{
}
