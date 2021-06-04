//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_VULKANCOMPUTESHADER_H
#define EAGLE_VULKANCOMPUTESHADER_H

#include <eagle/renderer/compute_shader.h>
#include <eagle/renderer/vulkan/vulkan_global_definitions.h>
#include <eagle/renderer/vulkan/vulkan_descriptor_set_layout.h>
#include <eagle/renderer/vulkan/vulkan_descriptor_set.h>

namespace eagle {

struct VulkanComputeShaderCreateInfo{
    VkDevice device;
    VkCommandPool commandPool;
    VkQueue computeQueue;
    uint32_t bufferCount;
    uint32_t* imageIndex;
};

class VulkanComputeShader : public ComputeShader {
public:
    VulkanComputeShader(const std::string &path, const VulkanComputeShaderCreateInfo &createInfo);

    ~VulkanComputeShader();

    void create_pipeline() override;

    void cleanup_pipeline() override;

    void dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) override;

    void update_image(uint32_t binding, const WeakPointer<Image>& image) override;

    void update_descriptors() override;

    void join() override;

    void clear_descriptor_set();
    void recreate(uint32_t bufferCount);

    inline VkPipeline &get_pipeline() { return m_computePipeline; }

    inline VkPipelineLayout &get_layout() { return m_pipelineLayout; }

private:

    void create_pipeline_layout();
    void create_descriptor_sets();
    void create_command_buffer();
    void create_fence();

private:

    VulkanComputeShaderCreateInfo m_createInfo;
    std::vector<uint32_t> m_code;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_computePipeline;
    std::vector<DescriptorBindingDescription> m_bindingDescriptions;
    StrongPointer<VulkanDescriptorSetLayout> m_descriptorLayout;
    StrongPointer<VulkanDescriptorSet> m_descriptorSet;
    VkCommandBuffer m_commandBuffer;
    VkFence m_fence;

    bool m_cleared = true;
};



}

#endif //EAGLE_VULKANCOMPUTESHADER_H
