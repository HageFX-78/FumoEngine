#include "BaseScene.h"
#include "GameObjectCollection.h"


namespace FumoEngine
{
	void BaseScene::activate() {
		initialize();
		on_activate();
	}

	void BaseScene::deactivate() {
		GameObjectCollection::dispose();
		on_deactivate();
	}

	void BaseScene::update(float deltaTime) {
		GameObjectCollection::update(deltaTime);
		on_update(deltaTime);
	}

	void BaseScene::render() {
		GameObjectCollection::render();
		on_render();
	}
}


