//
// Created by panchis on 4/03/21.
//

#pragma once
#include "vulkan_wrapper.h"
#include <iostream>
#include <string>
#include <vector>
#include "VDeleter.h"

class VulkanApplication {
public:
    VulkanApplication();
    virtual ~VulkanApplication();
    std::string run();
    std::string createInstance();
    std::string checkExtensionSupport();
    bool checkValidationSupport();
    std::string pickPhysicalDevice();
private:
    VkInstance vulkanInstance;
    void vulkanDestroy();
    VkResult CreateDebugReportCallbackExt();
    static void destroyDebuggerReportCallbackExt();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugReportFlagsEXT flags,
            VkDebugReportObjectTypeEXT objType,
            uint64_t obj,
            size_t location,
            int32_t code,
            const char* layerPrefix,
            const char* msg,
            void* user,
            void* userData){
        std::cerr << "Validation Layer: " << msg << std::endl;
        return VK_FALSE;
    }
    const std::vector<const char *> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
};

//#ifndef SILDUR_VULKAN_UTILS_H
//#define SILDUR_VULKAN_UTILS_H

//#endif //SILDUR_VULKAN_UTILS_H
