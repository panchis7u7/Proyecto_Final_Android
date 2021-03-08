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
    //Setup validation layers.
    setupDebugCallback();
    //Check extension support.
    message += checkExtensionSupport();
    //Pick a physical device.
    message += pickPhysicalDevice();
    return message;
}


//--------------------------------------------------------------------------------------------------
//Instance and physical device selection.

std::string VulkanApplication::createInstance(){
    /*if(enableValidationLayers && !checkValidationSupport()){
       std::cout << "No hay capas de validacion disponibles!" << std::endl;
    }*/

    std::vector<const char*> extensions = {"VK_KHR_surface",
                                           "VK_KHR_android_surface",
                                           "VK_EXT_swapchain_colorspace",
                                           "VK_KHR_get_surface_capabilities2",
                                           "VK_EXT_debug_report",
                                           "VK_KHR_get_physical_device_properties2",
                                           "VK_KHR_external_semaphore_capabilities",
                                           "VK_KHR_external_memory_capabilities",
                                           "VK_KHR_external_fence_capabilities"};

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
    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();
    if(checkValidationSupport()){
        std::cout << "Validation Layers are up!" << std:: endl;
        createInfo.enabledLayerCount = validationLayers.size();
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        std::cout << "Validation Layers aren't up!" << std::endl;
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = NULL;
    }

    if(vkCreateInstance(&createInfo, nullptr, &vulkanInstance) == VK_SUCCESS){
        return "Success at creating instance!\n";
    } else {
        return "Error!\n";
    }

}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Extension support.

std::string VulkanApplication::checkExtensionSupport() {
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
}

//--------------------------------------------------------------------------------------------------

void VulkanApplication::setupDebugCallback() {
    if(!enableValidationLayers)
        return;
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;

    if(CreateDebugReportCallbackExt(instance, &createInfo, nullptr, callback.replace()) != VK_SUCCESS)
        throw std::runtime_error("Failed to setup debug callback!");
    else
        std::cout << "Debug callback setup successful" << std::endl;
}

VkResult VulkanApplication::CreateDebugReportCallbackExt(
        VkInstance instance,
        const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugReportCallbackEXT* pCallback){
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if(func != nullptr)
        return func(instance, pCreateInfo, pAllocator, pCallback);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

//--------------------------------------------------------------------------------------------------

