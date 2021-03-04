//
// Created by panchis (Carlos Sebastian Madrigal Rodriguez) on 4/03/21.
//

#include "vulkan-utils.h"

std::string VulkanApplication::run() {
    vulkanInstance = VK_NULL_HANDLE;
    std::string message = "";
    message += vulkanInit();
    vulkanDestroy();
    return message;
}

void VulkanApplication::vulkanDestroy() {
    vkDestroyInstance(vulkanInstance, NULL);
}

std::string VulkanApplication::vulkanInit(){
    const char* instanceLayers[] = {"VK_LUNARG_standard_validation"};
    const char* instanceExtensions[] = {"VK_EXT_debug_report"};

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Instance";
    appInfo.pEngineName = "Mi Motor";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion = VK_MAKE_VERSION(1,2,171);

    VkInstanceCreateInfo  createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = 1;
    createInfo.ppEnabledExtensionNames = instanceExtensions;
    createInfo.enabledLayerCount = 1;
    createInfo.ppEnabledLayerNames = instanceLayers;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);
    if(result == VK_SUCCESS){
        return "Success!";
    } else {
        return "Error!";
    }

}