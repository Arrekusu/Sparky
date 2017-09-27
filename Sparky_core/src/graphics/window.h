#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
namespace sparky {	namespace graphics {
	class Window
	{
	private:
		friend struct GLFWwindow;
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;

		bool m_keys[MAX_KEYS];
		bool m_mouseButtons[MAX_BUTTONS];
		double mx, my;
	public:
		Window(const char *title, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		bool isKeyPressed(unsigned int keyCode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;
	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int node);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int node);
		friend static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
	};
} }