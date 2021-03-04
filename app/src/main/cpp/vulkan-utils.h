//
// Created by panchis on 4/03/21.
//

#pragma once
#include <vulkan/vulkan.h>
#include <string>

class VulkanApplication {
public:
    VkInstance vulkanInstance;
    std::string run();
private:
    std::string vulkanInit();
    void vulkanDestroy();
};

//#ifndef SILDUR_VULKAN_UTILS_H
//#define SILDUR_VULKAN_UTILS_H

//#endif //SILDUR_VULKAN_UTILS_H
