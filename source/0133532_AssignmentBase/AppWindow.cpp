#include "AppWindow.h"

namespace FumoEngine
{
	//Forward declaration
	void framebuffer_size_init(int width, int height);

	AppWindow::~AppWindow()
	{
		glfwTerminate();
	}
	int AppWindow::create(int width, int height, const char* title)
	{
		if (!glfwInit())
		{
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		//----- Window Callbacks ----
		data.width = width;
		data.height = height;
		data.title = title;
		glfwSetWindowUserPointer(window, &data);

		glfwSetWindowCloseCallback(window, [](::GLFWwindow* w) {
			void* ptr = glfwGetWindowUserPointer(w);
			WindowData* data = static_cast<WindowData*>(ptr);
			data->callback(close, 0);
			});

		glfwSetFramebufferSizeCallback(window, [](::GLFWwindow* w, int nWidth, int nHeight) {
			void* ptr = glfwGetWindowUserPointer(w);
			WindowData* data = static_cast<WindowData*>(ptr);

			data->width = nWidth;
			data->height = nHeight;

			if (nWidth == 0 || nHeight == 0) return;

			ViewportSizeData currentSize = { 0, 0, nWidth, nHeight };//Switched back to only use with and height for viewport but i didnt change the WindowEventData
			WindowEventData eventData(&currentSize);
			data->callback(resize, &eventData);
			});//*/
		framebuffer_size_init(width, height);//Reminder to self, runs only at start

		glClearColor(0.5, 0.5, 0.5, 1.0);

		return 1;
	}
	void AppWindow::swap_and_poll()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void AppWindow::setWindowEventCallback(const WindowEventCallbackFn& fn)
	{
		data.callback = fn;
	}

	::GLFWwindow* AppWindow::getWindowPtr()
	{
		return window;
	}

	Vector2 AppWindow::getWindowSize()
	{
		return Vector2(data.width, data.height);
	}

	void framebuffer_size_init(int width, int height)
	{
		if (width == 0 || height == 0) return;

		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);//Center render in the view

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

