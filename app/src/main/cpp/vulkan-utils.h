//
// Created by panchis on 4/03/21.
//

#pragma once
#include "vulkan_wrapper.h"
#include <string>

class VulkanApplication {
public:
    VulkanApplication();
    virtual ~VulkanApplication();
    std::string run();
    std::string extensionSupport();
private:
    VkInstance vulkanInstance;
    std::string vulkanInit();
    void vulkanDestroy();
};

//#ifndef SILDUR_VULKAN_UTILS_H
//#define SILDUR_VULKAN_UTILS_H

//#endif //SILDUR_VULKAN_UTILS_H
