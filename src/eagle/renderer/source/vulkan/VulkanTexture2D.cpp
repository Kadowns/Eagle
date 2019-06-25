//
// Created by Novak on 19/06/2019.
//

#include "eagle/renderer/vulkan/VulkanTexture2D.h"
#include "eagle/renderer/vulkan/VulkanHelper.h"

_EAGLE_BEGIN

VulkanTexture2D::VulkanTexture2D(const Texture2DCreateInfo &textureCreateInfo,
                                 const VulkanTexture2DCreateInfo &vulkanInfo) :
        Texture2D(textureCreateInfo),
        m_vulkanInfo(vulkanInfo),
        m_image(std::make_shared<VulkanImage>()){
    upload_pixel_data();
}

VulkanTexture2D::~VulkanTexture2D() {
    VK_CALL
    vkDestroySampler(m_vulkanInfo.device, m_image->sampler, nullptr);
    VK_CALL
    vkDestroyImageView(m_vulkanInfo.device, m_image->view, nullptr);
    VK_CALL
    vkDestroyImage(m_vulkanInfo.device, m_image->image, nullptr);
    VK_CALL
    vkFreeMemory(m_vulkanInfo.device, m_image->memory, nullptr);
}

void VulkanTexture2D::upload_pixel_data() {

    std::shared_ptr<VulkanBuffer> stagingBuffer;
    VulkanBufferCreateInfo bufferInfo = {};
    bufferInfo.memoryFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    bufferInfo.usageFlags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

    VK_CALL
    VulkanBuffer::create_buffer(
            m_vulkanInfo.physicalDevice,
            m_vulkanInfo.device,
            stagingBuffer,
            bufferInfo,
            m_textureInfo.pixels.size(),
            m_textureInfo.pixels.data()
    );

    VK_CALL
    VulkanHelper::create_image(m_vulkanInfo.physicalDevice, m_vulkanInfo.device,
                               m_textureInfo.width, m_textureInfo.height, m_textureInfo.mipLevels,
                               m_textureInfo.layerCount,
                               VK_FORMAT_R8G8B8A8_UNORM,
                               VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                               VK_SHARING_MODE_EXCLUSIVE,
                               m_image->image, m_image->memory, 0);

    VkImageSubresourceRange subresourceRange = {};
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.baseArrayLayer = 0;
    subresourceRange.layerCount = 1;

    VK_CALL
    VulkanHelper::transition_image_layout(m_vulkanInfo.device, m_vulkanInfo.commandPool, m_vulkanInfo.graphicsQueue,
                                          m_image->image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED,
                                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, subresourceRange);

    copy_buffer_to_image(stagingBuffer, m_image->image, m_textureInfo.width, m_textureInfo.height);

    VK_CALL
    VulkanHelper::transition_image_layout(m_vulkanInfo.device, m_vulkanInfo.commandPool, m_vulkanInfo.graphicsQueue,
                                          m_image->image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                          VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, subresourceRange);

    stagingBuffer->destroy();

    VulkanHelper::create_image_view(m_vulkanInfo.device, m_image->image, m_image->view, VK_FORMAT_R8G8B8A8_UNORM,
                                    VK_IMAGE_VIEW_TYPE_2D, subresourceRange);


    VulkanHelper::create_image_sampler(m_vulkanInfo.device, m_image->sampler, VK_SAMPLER_ADDRESS_MODE_REPEAT);
}

void
VulkanTexture2D::copy_buffer_to_image(std::shared_ptr<VulkanBuffer> buffer, VkImage image, uint32_t width,
                                      uint32_t height) {

    VkCommandBuffer commandBuffer = VulkanHelper::begin_single_time_commands(m_vulkanInfo.device,
                                                                             m_vulkanInfo.commandPool);

    VkBufferImageCopy region = {};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

    region.imageOffset = {0, 0, 0};
    region.imageExtent = {
            width,
            height,
            1
    };

    vkCmdCopyBufferToImage(
            commandBuffer,
            buffer->get_native_buffer(),
            image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1,
            &region
    );

    VulkanHelper::end_single_time_commnds(m_vulkanInfo.device, m_vulkanInfo.commandPool, commandBuffer,
                                          m_vulkanInfo.graphicsQueue);
}

_EAGLE_END

