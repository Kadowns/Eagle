//
// Created by Novak on 31/08/2019.
//

#ifndef EAGLE_VULKANCONVERTER_H
#define EAGLE_VULKANCONVERTER_H

#include <eagle/renderer/render_pass.h>
#include <eagle/renderer/command_buffer.h>
#include "vulkan_global_definitions.h"

namespace eagle {

class VulkanConverter {
public:
    static VkFormat to_vk(Format format);
    static Format to_eg(VkFormat format);
    static VkShaderStageFlags to_vk(ShaderStage stage);
    static ShaderStage to_eg(VkShaderStageFlags stage);
    static VkDescriptorType to_vk(DescriptorType type);
    static DescriptorType to_eg(VkDescriptorType type);
    static VkFilter to_vk(Filter filter);
    static Filter to_eg(VkFilter filter);
    static VkPrimitiveTopology to_vk(PrimitiveTopology topology);
    static PrimitiveTopology to_eg(VkPrimitiveTopology topology);
    static AttachmentLoadOperator to_eg(VkAttachmentLoadOp op);
    static VkAttachmentLoadOp to_vk(AttachmentLoadOperator op);
    static AttachmentStoreOperator to_eg(VkAttachmentStoreOp op);
    static VkAttachmentStoreOp to_vk(AttachmentStoreOperator op);
    static VkImageLayout to_vk(ImageLayout op);
    static ImageLayout to_eg(VkImageLayout op);
    static VkAttachmentDescription to_vk(const RenderAttachmentDescription &egAttachment);
    static RenderAttachmentDescription to_eg(const VkAttachmentDescription &vkAttachment);
    static VkImageTiling to_vk(ImageTiling tiling);
    static ImageTiling to_eg(VkImageTiling tiling);
    static ImageUsage to_eg(VkImageUsageFlagBits usage);
    static VkImageUsageFlagBits to_vk(ImageUsage usage);
    static ImageAspect to_eg(VkImageAspectFlagBits aspect);
    static VkImageAspectFlagBits to_vk(ImageAspect aspect);
    static MemoryProperty to_eg(VkMemoryPropertyFlagBits property);
    static VkMemoryPropertyFlagBits to_vk(MemoryProperty property);
    static PipelineStage to_eg(VkPipelineStageFlagBits stage);
    static VkPipelineStageFlagBits to_vk(PipelineStage stage);
    static VkCommandBufferLevel to_vk(CommandBufferLevel level);
    static CommandBufferLevel to_eg(VkCommandBufferLevel level);
    static VkVertexInputRate to_vk(VertexInputRate rate);
    static VertexInputRate to_eg(VkVertexInputRate rate);
    static VkCullModeFlags to_vk(CullMode mode);
    static CullMode to_eg(VkCullModeFlagBits mode);

    template<typename EG, typename VK>
    static std::vector<EG> eg_vector_from_vk_flags(VK flags){
        static_assert(sizeof(VK) * 8 == 32, "Only 32 bits flags are supported");
        std::vector<EG> result;
        uint32_t bit = 0;
        while (bit < 32){
            uint32_t flag = flags & (1u << bit);
            if (flag) {
                result.emplace_back(to_eg(static_cast<VK>(flag)));
            }

            bit++;
        }
        return result;
    }

    template<typename VK, typename EG>
    static VK to_vk_flags(const std::vector<EG>& elements) {
        VK flags = 0;
        for (auto &element : elements) {
            flags |= to_vk(element);
        }
        return flags;
    }

    template<typename EG, typename VK>
    static std::vector<EG> to_eg_vector(const std::vector<VK>& elements){
        std::vector<EG> result;
        result.reserve(elements.size());
        for (auto& element : elements){
            result.emplace_back(to_eg(element));
        }
        return result;
    }

    template<typename VK, typename EG>
    static std::vector<VK> to_vk_vector(const std::vector<EG>& elements){
        std::vector<VK> result;
        result.reserve(elements.size());
        for (auto& element : elements){
            result.emplace_back(to_vk(element));
        }
        return result;
    }

};

}

#endif //EAGLE_VULKANCONVERTER_H
