#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

namespace FumoEngine
{
	/// <summary>
	/// Base scene of all scenes to be created in the engine, provides boilerplate template for users to create custom logic in.
	/// </summary>
	class BaseScene
	{
	public:

		void activate();
		void deactivate();
		void update(float deltaTime);
		void render();

		virtual std::string getName() const = 0;

	protected:
		// pure virtual
		virtual void initialize() = 0;

		virtual void on_activate() {};
		virtual void on_deactivate() {};
		virtual void on_update(float deltaTime) {};
		virtual void on_render() {};
	};
}
