#include <iostream>
#include <vulkan/vulkan.h>

int main()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Pong";
    appInfo.pEngineName = "PongEngine";

    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;

    VkInstance instance;

    VkResult res = vkCreateInstance(&instanceInfo, 0, &instance);

    if (res == VK_SUCCESS)
    {
        std::cout << "Wee i live" << std::endl;
    }

    return 0;
}