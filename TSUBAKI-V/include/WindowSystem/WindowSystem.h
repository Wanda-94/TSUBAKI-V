#pragma once

#include "GlobalSetting/IncludeFile.h"
#include "GlobalSetting/GlobalSetting.h"

class WindowSystem {
public:
	WindowSystem() {
		InitWindowSystem();
	}
	~WindowSystem() {
		DestroyWindowSystem();
	}
	GLFWwindow* GetWindowHandle() { return m_glfw_window; }
	bool WindowShouldClose() { return glfwWindowShouldClose(m_glfw_window); }
private:
	void InitWindowSystem() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_glfw_window = glfwCreateWindow(GScreenWidth, GScreenHeight, GWindowTitle, nullptr, nullptr);
	}
	void DestroyWindowSystem() {
		glfwDestroyWindow(m_glfw_window);
	}
	GLFWwindow* m_glfw_window;
};
