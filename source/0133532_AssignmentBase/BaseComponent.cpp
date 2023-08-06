#include "BaseComponent.h"
BaseComponent::BaseComponent(GameObject* go) : gameObject(go) {}
BaseComponent::~BaseComponent() {}
void BaseComponent::awake() {}
void BaseComponent::start() {}
void BaseComponent::update(float deltaTime) {}
void BaseComponent::render() {}

void BaseComponent::destroy()
{
	flaggedForDeletion = true;
}
bool BaseComponent::shouldDestroy()
{
	return flaggedForDeletion;
}