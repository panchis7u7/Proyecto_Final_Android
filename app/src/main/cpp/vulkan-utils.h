//
// Created by panchis on 4/03/21.
//

#pragma once
#include "vulkan_wrapper.h"
#include <iostream>
#include <string>
#include <vector>

class VulkanApplication {
public:
    VulkanApplication();
    virtual ~VulkanApplication();
    std::string run();
    std::string createInstance();
    std::string extensionSupport();
    bool checkValidationSupport();
    std::string pickPhysicalDevice();
private:
    bool enableValidationLayers = false;
    VkInstance vulkanInstance;
    void vulkanDestroy();
    const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
};

//#ifndef SILDUR_VULKAN_UTILS_H
//#define SILDUR_VULKAN_UTILS_H

//#endif //SILDUR_VULKAN_UTILS_H
