//
// Created by panchis (Carlos Sebastian Madrigal Rodriguez) on 4/03/21.
//

#include "vulkan-utils.h"
#include <cstring>
#include <android/log.h>
#include <map>

VulkanApplication::VulkanApplication() {
    InitVulkan();
}

VulkanApplication::~VulkanApplication() {
    //vkDestroyInstance(vulkanInstance, NULL);
}

std::string VulkanApplication::run() {
    std::string message = "";
    //Create instance, extension support and validation layers.
    message += createInstance();
    //Setup validation layers.
    //if(checkValidationSupport())
    //setupDebugCallback();
    //Check extension support.
    message += checkExtensionSupport();
    //Pick a physical device.
    message += pickPhysicalDevice();
    message += createLogicalDevice();
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

/*void VulkanApplication::setupDebugCallback() {
    if(checkValidationSupport())
    //if(!enableValidationLayers)
        return;
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;

    if(CreateDebugReportCallbackExt(instance, &createInfo, nullptr, callback.replace()) != VK_SUCCESS)
        throw std::runtime_error("Failed to setup debug callback!");
    else
        std::cout << "Debug callback setup successful" << std::endl;
}*/
/*
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
}*/

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Pick a physical device.

std::string VulkanApplication::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    if (VK_SUCCESS != vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, NULL) || deviceCount == 0) {
        std::cout << "Failed searching for Vulkan physical devices\n";
        return "No device found!\n";
    }

    std::vector<VkPhysicalDevice> physical_devices(deviceCount);
    if (VK_SUCCESS != vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, physical_devices.data()) ||
        deviceCount == 0) {
        std::cout << "Failed enumerating Vulkan physical devices\n";
        return "Failed enumerating Vulkan physical devices\n";
    }

    std::multimap<int, VkPhysicalDevice> rankedDevices;

    for(const auto& currentDevice : physical_devices){
        int score = rateDeviceSuitability(currentDevice);
        rankedDevices.insert(std::make_pair(score, currentDevice));
    }

    //Start from the end (start).
    if(rankedDevices.rbegin()->first > 0)
        physicalDevice = rankedDevices.rbegin()->second;
    else
        throw std::runtime_error("No physical device found!");

    return "Physical device found!!\n";
}

int VulkanApplication::rateDeviceSuitability(VkPhysicalDevice deviceToRate){
    int score = 0;

    QueueFamilyIndices indices = findQueueFamilies(deviceToRate);
    if(!indices.isComplete())
        return 0;

    VkPhysicalDeviceFeatures deviceFeatures;
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(deviceToRate, &deviceProperties);
    vkGetPhysicalDeviceFeatures(deviceToRate, &deviceFeatures);

    if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;
    score += deviceProperties.limits.maxImageDimension2D;
    if(!deviceFeatures.geometryShader)
        return 0;

    return score;
}

//--------------------------------------------------------------------------------------------------

std::string VulkanApplication::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.pNext = nullptr;
    queueCreateInfo.flags = 0;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
    queueCreateInfo.queueCount = 1;
    const float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = nullptr;
    createInfo.pEnabledFeatures = &deviceFeatures;

    if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS)
        throw std::runtime_error("Failed to create logical device!\n");

    vkGetDeviceQueue(logicalDevice, indices.graphicsFamily, 0, &graphicsQueue);

    return "Logical device created successfuly!\n";
}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Queue family.

QueueFamilyIndices VulkanApplication::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);//

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for(const auto& queueFamily : queueFamilies){
        if(queueFamily.queueCount > 0 && queueFamily.queueFlags && VK_QUEUE_GRAPHICS_BIT){
            indices.graphicsFamily = i;
        }
        if (indices.isComplete())
            break;
        i++;
    }
    return indices;
}

//--------------------------------------------------------------------------------------------------
