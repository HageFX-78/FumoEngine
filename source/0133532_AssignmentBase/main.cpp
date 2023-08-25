#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "Application.h"


int main()
{	
	Application app;
	app.initialize(800, 800, "GL window");
	app.run();
	app.shutdown();
}
