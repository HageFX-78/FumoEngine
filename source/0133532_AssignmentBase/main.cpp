#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "Application.h"

namespace Fumo = FumoEngine;

int main()
{	
	Fumo::Application app;
	app.initialize(800, 800, "GL window");
	app.run();
	app.shutdown();
}
