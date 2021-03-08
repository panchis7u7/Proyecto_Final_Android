//
// Created by panchis (Carlos Sebastian Madrigal Rodriguez) on 4/03/21.
//

#include "vulkan-utils.h"
#include <cstring>
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
    //Create instance, extension support and validation layers.
    message += createInstance();
    //Check extension support.
    message += extensionSupport();
    //Pick a physical device.
    message += pickPhysicalDevice();
    return message;
}


//--------------------------------------------------------------------------------------------------
//Instance and physical device selection.

std::string VulkanApplication::createInstance(){
    if(enableValidationLayers && !checkValidationSupport()){
        throw std::runtime_error("validation layers requested, but not available!");
    }

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
    //createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    //createInfo.ppEnabledLayerNames = validationLayers.data();
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = NULL;

    //Check validation layers.
    /*VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        //populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }*/

    if(vkCreateInstance(&createInfo, nullptr, &vulkanInstance) == VK_SUCCESS){
        return "Success at creating instance!\n";
    } else {
        return "Error!\n";
    }

}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Extension support.

std::string VulkanApplication::extensionSupport() {
    std::string ext = "";
    uint32_t extensionCount = 0;
    //Request del numero de extensiones disponibles.
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensiones(extensionCount);
    //extensiones.reserve(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensiones.data());
    for(const auto& extension : extensiones){
        ext += "\t" + std::string(extension.extensionName) + "\n";
    }
    return ext;
}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Validation Layers (TODO)

bool VulkanApplication::checkValidationSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for(const char* layerName : validationLayers){
        bool layerFound = false;
        for(const auto& layerProperties : availableLayers){
            if(strcmp(layerName, layerProperties.layerName) == 0){
                layerFound = true;
                break;
            }
        }
        if(layerFound)
            return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Pick a physical device.

std::string VulkanApplication::pickPhysicalDevice() {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;
    if (VK_SUCCESS != vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, NULL) || deviceCount == 0) {
        std::cout << "Failed searching for Vulkan physical devices\n";
        return "No device found!\n";
    }

    std::vector<VkPhysicalDevice> physical_devices;
    physical_devices.reserve(deviceCount);
    if (VK_SUCCESS != vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, physical_devices.data()) ||
        deviceCount == 0) {
        std::cout << "Failed enumerating Vulkan physical devices\n";
        return "Failed enumerating Vulkan physical devices\n";
    }

    return "nel";

    if(physicalDevice == VK_NULL_HANDLE){
        return  "Failed to find a suitable GPU.\n";
    }
}

//--------------------------------------------------------------------------------------------------