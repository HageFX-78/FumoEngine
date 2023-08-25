#include "SplashScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "GameObjectCollection.h"

#include "TransformComponent.h"
#include "RendererComponent.h"
#include "ProgressBar.h"
#include "SpriteRenderer.h"

namespace Showcase
{
	std::string SplashScene::getName() const {
		return "SplashScene";
	}
	void SplashScene::initialize() {
		go1 = new Fumo::GameObject("SplashBar");
		go1->transform->setYPosition(-80);
		go1->addComponent<Fumo::ProgressBar>();
		go1->getComponent<Fumo::ProgressBar>()->setProgress(1.0f);
		go1->getComponent<Fumo::ProgressBar>()->setBackDropColor(255.0f, 247.0f, 212.0f, 0.6f);
		go1->getComponent<Fumo::ProgressBar>()->setBarColor(171.0f, 216.0f, 238.0f, 1.0f);


		go2 = new Fumo::GameObject("Fumo");
		go2->addComponent<Fumo::SpriteRenderer>();
		go2->transform->setScale(2.0f, 2.0f);
		go2->transform->setYPosition(80);

		std::cout << std::endl << "[ KEY ] Space to skip" << std::endl << std::endl;

	}

	void SplashScene::on_activate() {
		glClearColor(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1);
		time = 0;
	}

	void SplashScene::on_update(float deltaTime) {
		time += deltaTime;

		if (go1 != nullptr && time <= sceneSwitchTime)
			go1->getComponent<Fumo::ProgressBar>()->setProgress(time / sceneSwitchTime);

		if (time >= sceneSwitchTime)
			Fumo::SceneStateMachine::loadScene("FUMONIA");

		if (Fumo::Input::getKeyDown(GLFW_KEY_SPACE))
		{
			Fumo::SceneStateMachine::loadScene("FUMONIA");
		}
	}

	void SplashScene::on_render() {

	}
}
