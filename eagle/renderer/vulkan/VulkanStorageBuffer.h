//
// Created by Novak on 01/04/2020.
//

#ifndef EAGLE_VULKANSTORAGEBUFFER_H
#define EAGLE_VULKANSTORAGEBUFFER_H

#include <eagle/renderer/StorageBuffer.h>
#include <eagle/renderer/vulkan/VulkanCore.h>
#include "VulkanBuffer.h"
#include "VulkanCleaner.h"

namespace eagle {

struct VulkanStorageBufferCreateInfo{
    VkDevice device;
    VkPhysicalDevice physicalDevice;
    size_t bufferCount;
    VkCommandPool commandPool;
    VkQueue graphicsQueue;
};

class VulkanStorageBuffer : public StorageBuffer, public VulkanCleanable {
public:
    explicit VulkanStorageBuffer(VulkanStorageBufferCreateInfo createInfo, size_t size, void* data, UpdateType usage);
    virtual ~VulkanStorageBuffer();
    virtual void set_data(void *data, size_t size, size_t offset) override;
    virtual void push() override;

    DescriptorType type() const override;

    virtual bool is_dirty() const override;
    virtual void flush(uint32_t index) override;

    void cleanup();
    void recreate(uint32_t bufferCount);
    void create_storage_buffer();

    inline std::vector<std::shared_ptr<VulkanBuffer>>& get_buffers() { return m_buffers; }
private:
    VulkanStorageBufferCreateInfo m_createInfo;

    std::vector<std::shared_ptr<VulkanBuffer>> m_buffers;
    std::set<int> m_dirtyBuffers;
    bool m_cleared = true;
    bool m_dirtyBytes = false;

};

}

#endif //EAGLE_VULKANSTORAGEBUFFER_H