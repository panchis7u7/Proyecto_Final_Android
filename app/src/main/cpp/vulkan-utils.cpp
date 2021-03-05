//
// Created by panchis (Carlos Sebastian Madrigal Rodriguez) on 4/03/21.
//

#include "vulkan-utils.h"
#include <vector>
#include <android/log.h>

VulkanApplication::VulkanApplication() {
    InitVulkan();
}

VulkanApplication::~VulkanApplication() {
    vkDestroyInstance(vulkanInstance, NULL);
}

std::string VulkanApplication::run() {
    vulkanInstance = VK_NULL_HANDLE;
    std::string message = "";
    message += vulkanInit();
    return message;
}

std::string VulkanApplication::extensionSupport() {
    std::string ext = "";
    uint32_t extensionCount = 0;
    //Request del numero de extensiones disponibles.
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensiones(extensionCount);
    //extensiones.reserve(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensiones.data());
    for(const auto& extension : extensiones){
        ext += "\n" + std::string(extension.extensionName) + "\n";
    }
    return ext;
}

std::string VulkanApplication::vulkanInit(){
    //const char* instanceLayers[] = {"VK_LUNARG_standard_validation"};
    //const char* instanceExtensions[] = {"VK_EXT_debug_report"};

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Instance";
    appInfo.pEngineName = "Mi Motor";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo  createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount =0;
    createInfo.ppEnabledExtensionNames = NULL;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = NULL;

    std::string msg = extensionSupport();

    if(vkCreateInstance(&createInfo, nullptr, &vulkanInstance) == VK_SUCCESS){
        return msg+"Success!";
    } else {
        return msg+"Error!";
    }

}