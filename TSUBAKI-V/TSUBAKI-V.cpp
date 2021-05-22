// TSUBAKI-V.cpp: 定义应用程序的入口点。
//

#include "TSUBAKI-V.h"
#include "vulkan/vulkan.hpp"
#include "GLFW/glfw3.h"

int main()
{
	//GLFWwindow* window = glfwCreateWindow(1080,1920,"TSUBAKI-V",nullptr,nullptr);
	//while (!glfwWindowShouldClose(window))
	//{
	//	cout << "run" << endl;
	//}
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800,600,"Vulkan",nullptr,nullptr);
	uint32_t extension_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr,&extension_count,nullptr);

	std::cout << "extensions supported " << extension_count << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
