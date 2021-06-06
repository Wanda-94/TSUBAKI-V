#pragma once


#include "GlobalSetting/IncludeFile.h"

class RHI;

extern RHI* GRHI;

enum class RHIType {
	RHI_VULKAN,
	RHI_MAX
};

class RHI {
public:
	RHI() {}
	virtual ~RHI() {}

	static void CreateRHIInstance();

	virtual void InitRHI() = 0;
	virtual void DestroyRHI() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual RHIType GetRHIType() = 0;

private:

};

class VulkanRHI : public RHI {
public:
	VulkanRHI();
	virtual ~VulkanRHI() {}
	virtual void InitRHI() override;
	virtual void DestroyRHI() override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;
	virtual RHIType GetRHIType() override;
private:
	void InitVulkanInstance();
	void InitPhysicalDevice();
	void InitDevice();
	void ConnectNativeWindowHandle(GLFWwindow* glfw_window);

	VkInstance m_vk_instance;
	VkPhysicalDevice m_vk_physical_device;
	VkDevice m_vk_device;
	VkQueue m_vk_queue;
	VkSurfaceKHR m_vk_surface;
	//
	uint32_t m_vk_queue_family_index = 0;
};

