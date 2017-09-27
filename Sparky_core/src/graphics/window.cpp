#include "window.h"

namespace sparky {	namespace graphics {

	void window_resize(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init()) {
			glfwTerminate();
		}

		for (int i = 0; i < MAX_KEYS; i++) {
			m_keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_mouseButtons[i] = false;
		}

	}

	Window::~Window() 
	{
		glfwTerminate();
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::isKeyPressed(unsigned int keyCode) const
	{
		if (keyCode >= MAX_KEYS) {
			return false;
		}
		return m_keys[keyCode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		if (button >= MAX_BUTTONS) {
			return false;
		}
		return m_mouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = mx;
		y = my;
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create glfwWindow" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0.0);

		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialize GLEW!!" << std::endl;
			return false;
		}
		return true;
	}

	void Window::update() 
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL error " << error << std::endl;
		}
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void window_resize(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int node) {
		Window* win = (Window*) glfwGetWindowUserPointer(window);		
		win->m_keys[key] = action != GLFW_RELEASE;
	}
	void mouse_button_callback(GLFWwindow * window, int button, int action, int node)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mouseButtons[button] = action != GLFW_RELEASE;
	}
	void cursor_position_callback(GLFWwindow * window, double xPos, double yPos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xPos;
		win->my = yPos;
	}
} }