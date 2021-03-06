#include <jni.h>
#include <string>
#include "vulkan-utils.h"

extern "C" JNIEXPORT jstring JNICALL Java_com_app_sildur_MainActivity_startVulkanJNI( JNIEnv* env, jobject /* this */) {
    VulkanApplication vk;
    std::string message = vk.run();
    //std::string hello = "Hello from C++";
    //return env->NewStringUTF(hello.c_str());
    return env->NewStringUTF(message.c_str());
}