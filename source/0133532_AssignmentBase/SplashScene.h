#pragma once

#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>

#include "angle_util/matrix.h"
#include "angle_util/vector.h"

namespace Fumo = FumoEngine;
namespace Showcase
{
	class SplashScene : public Fumo::BaseScene {
	public:
		std::string getName() const override;

	protected:
		void initialize() override;
		void on_activate() override;
		void on_update(float deltaTime) override;
		void on_render() override;

		float time;
		float sceneSwitchTime = 10.0f;
	private:
		Fumo::GameObject* go1;
		Fumo::GameObject* go2;
	};
}


