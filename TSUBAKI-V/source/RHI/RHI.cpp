#include "RHI/RHI.h"
#include <iostream>
#include "GlobalSetting/GlobalSetting.h"
#include "GlobalSetting/IncludeFile.h"
#include "Engine/Engine.h"

#define VK_CHECK(Function) if( Function != VK_SUCCESS )\
{ LOG(LogType::LOG_ERROR,"VK Error In Line "+std::to_string( __LINE__ )); }

RHI* GRHI = nullptr;

void RHI::CreateRHIInstance()
{
	LOG(LogType::LOG_MESSAGE,"Init RHI With Vulkan API.");
	GRHI = new VulkanRHI();
}

VulkanRHI::VulkanRHI() :m_vk_device(VK_NULL_HANDLE), m_vk_physical_device(VK_NULL_HANDLE), m_vk_instance(VK_NULL_HANDLE)
{

}

void VulkanRHI::InitRHI()
{
	InitVulkanInstance();
	InitPhysicalDevice();
	InitDevice();
	ConnectNativeWindowHandle(GEngine->GetWindowSystem()->GetWindowHandle());
}

void VulkanRHI::DestroyRHI()
{
}

void VulkanRHI::BeginFrame()
{
}

void VulkanRHI::EndFrame()
{
}

RHIType VulkanRHI::GetRHIType()
{
	return RHIType::RHI_VULKAN;
}

//void CheckDeviceQueueFamilies(const VkPhysicalDevice& physical_device)
//{
//
//	std::unordered_map<std::string, VkQueueFlagBits> vk_queue_flag_name_map{
//	std::pair<std::string,VkQueueFlagBits>("VK_QUEUE_COMPUTE_BIT",VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT),
//	std::pair<std::string,VkQueueFlagBits>("VK_QUEUE_FLAG_BITS_MAX_ENUM",VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM),
//	std::pair<std::string,VkQueueFlagBits>("VK_QUEUE_GRAPHICS_BIT",VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT),
//	std::pair<std::string,VkQueueFlagBits>("VK_QUEUE_PROTECTED_BIT",VkQueueFlagBits::VK_QUEUE_PROTECTED_BIT),
//	std::pair<std::string,VkQueueFlagBits>("VK_QUEUE_SPARSE_BINDING_BIT",VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT),
//	std::pair<std::string,VkQueueFlagBits>("VK_QUEUE_TRANSFER_BIT",VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT),
//	};
//
//	uint32_t queue_family_count;
//	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
//	std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);
//	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_family_properties.data());
//	for (const auto& queue_family_property : queue_family_properties)
//	{//the index later use in get queue handl is the index we get families.... some tutorial always set 0 , because the first always be most stronge famliy
//		std::cout << "queue count " << (queue_family_property.queueCount) << std::endl;
//		for (const auto& element : vk_queue_flag_name_map)
//		{
//			if ((element.second & queue_family_property.queueFlags) != 0)
//			{
//				std::cout << "	" << element.first << std::endl;
//			}
//		}
//	}
//}

bool IsSuitableDevice(VkPhysicalDeviceProperties& device_property, VkPhysicalDeviceFeatures& device_feature)
{
	return true;
}

void VulkanRHI::InitVulkanInstance()
{
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = GWindowTitle;
	app_info.pEngineName = "None";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pApplicationInfo = &app_info;
	instance_create_info.enabledExtensionCount = 0;
	instance_create_info.ppEnabledExtensionNames = nullptr;
	instance_create_info.enabledLayerCount = 0;

	VK_CHECK(vkCreateInstance(&instance_create_info, nullptr, &m_vk_instance));

}

void VulkanRHI::InitPhysicalDevice()
{
	uint32_t physical_device_count = 0;
	vkEnumeratePhysicalDevices(m_vk_instance, &physical_device_count, nullptr);
	if (physical_device_count == 0)
	{
		LOG(LogType::LOG_MESSAGE, "No GPU Find.");
	}
	else
	{
		LOG(LogType::LOG_MESSAGE, std::to_string(physical_device_count) + " GPU Find.");
	}
	std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
	vkEnumeratePhysicalDevices(m_vk_instance, &physical_device_count, physical_devices.data());
	for (const auto& physical_device : physical_devices)
	{
		VkPhysicalDeviceProperties physical_device_property;
		VkPhysicalDeviceFeatures physical_device_feature;
		vkGetPhysicalDeviceFeatures(physical_device, &physical_device_feature);
		vkGetPhysicalDeviceProperties(physical_device, &physical_device_property);
		if (IsSuitableDevice(physical_device_property, physical_device_feature))
		{
			LOG(LogType::LOG_MESSAGE, "1 GPU Suitable");
			//CheckDeviceQueueFamilies(physical_device);
			m_vk_physical_device = physical_device;
			break;
		}
	}
}

void VulkanRHI::InitDevice()
{
	float priority = 1.0f;
	VkDeviceQueueCreateInfo queue_create_info{};
	queue_create_info.queueFamilyIndex = m_vk_queue_family_index;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &priority;

	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.pQueueCreateInfos = &queue_create_info;
	device_create_info.queueCreateInfoCount = 1;

	VK_CHECK(vkCreateDevice(m_vk_physical_device, &device_create_info, nullptr, &m_vk_device));
	vkGetDeviceQueue(m_vk_device,0,0,&m_vk_queue);
}

void VulkanRHI::ConnectNativeWindowHandle(GLFWwindow* glfw_window)
{
	VkWin32SurfaceCreateInfoKHR window_create_info{};
	window_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	window_create_info.hwnd = glfwGetWin32Window(glfw_window);
	window_create_info.hinstance = GetModuleHandle(nullptr);
	//NOT ENABLE EXTENSION...
	VK_CHECK(vkCreateWin32SurfaceKHR(m_vk_instance, &window_create_info, nullptr, &m_vk_surface));

	VkBool32 present_support = false;
	vkGetPhysicalDeviceSurfaceSupportKHR(m_vk_physical_device, 0, m_vk_surface, &present_support);
	if (!present_support)
	{
		LOG(LogType::LOG_ERROR, "Not Support Surface Present");
	}
}