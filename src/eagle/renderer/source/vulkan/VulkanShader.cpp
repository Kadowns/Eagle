
#include "eagle/renderer/vulkan/VulkanShader.h"
#include "eagle/renderer/ShaderItemLayout.h"
#include "eagle/core/Log.h"

#include <fstream>


_EAGLE_BEGIN

VulkanShader::VulkanShader(const std::string& vertFileName, const std::string& fragFileName, const VulkanShaderCreateInfo& createInfo) :
    Shader(vertFileName, fragFileName),
    m_cleared(true),
    m_createInfo(createInfo){
    create_pipeline();
}

VulkanShader::~VulkanShader() {
    cleanup_pipeline();
}

void VulkanShader::create_pipeline() {
    EG_CORE_TRACE("Creating shader pipeline!");

    m_layoutBindings.emplace_back(create_descriptor_set_layout_binding(
            0,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            1,
            VK_SHADER_STAGE_VERTEX_BIT,
            nullptr
            ));
    m_uniformLayouts["mvp"] = ShaderItemLayout({SHADER_ITEM_COMPONENT_MAT4});

    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
    descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(m_layoutBindings.size());
    descriptorSetLayoutInfo.pBindings = m_layoutBindings.data();

    VK_CALL_ASSERT(vkCreateDescriptorSetLayout(m_createInfo.device, &descriptorSetLayoutInfo, nullptr, &m_descriptorSetLayout)) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }

    VkShaderModule vertShaderModule = create_shader_module(m_vertShaderCode);
    VkShaderModule fragShaderModule = create_shader_module(m_fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    ShaderItemLayout vertexLayout({SHADER_ITEM_COMPONENT_VEC2, SHADER_ITEM_COMPONENT_VEC3});
    VkVertexInputBindingDescription inputBinding = get_binding_description(vertexLayout);
    std::vector<VkVertexInputAttributeDescription> inputAttributes = get_attribute_descriptions(vertexLayout);

    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &inputBinding;
    vertexInputInfo.vertexAttributeDescriptionCount = inputAttributes.size();
    vertexInputInfo.pVertexAttributeDescriptions = inputAttributes.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) m_createInfo.extent.width;
    viewport.height = (float) m_createInfo.extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = m_createInfo.extent;

    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &m_descriptorSetLayout;

    VK_CALL_ASSERT(vkCreatePipelineLayout(m_createInfo.device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout)) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.layout = m_pipelineLayout;
    pipelineInfo.renderPass = m_createInfo.renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    VK_CALL_ASSERT(vkCreateGraphicsPipelines(m_createInfo.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline)) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    VK_CALL vkDestroyShaderModule(m_createInfo.device, fragShaderModule, nullptr);
    VK_CALL vkDestroyShaderModule(m_createInfo.device, vertShaderModule, nullptr);

    m_cleared = false;

    EG_CORE_TRACE("Shader pipeline created!");
}

void VulkanShader::cleanup_pipeline(){
    if (m_cleared){ return; }
    VK_CALL vkDestroyPipeline(m_createInfo.device, m_graphicsPipeline, nullptr);
    VK_CALL vkDestroyPipelineLayout(m_createInfo.device, m_pipelineLayout, nullptr);
    m_cleared = true;
}

VkDescriptorSetLayoutBinding VulkanShader::create_descriptor_set_layout_binding(
        uint32_t binding,
        VkDescriptorType type,
        uint32_t descriptorCount,
        VkShaderStageFlags flags,
        const VkSampler * pImmutableSamplers) {

    VkDescriptorSetLayoutBinding descriptorBinding = {};
    descriptorBinding.binding = binding;
    descriptorBinding.descriptorType = type;
    descriptorBinding.descriptorCount = descriptorCount;
    descriptorBinding.stageFlags = flags;
    descriptorBinding.pImmutableSamplers = pImmutableSamplers;
    return descriptorBinding;
}

VkVertexInputBindingDescription VulkanShader::get_binding_description(const ShaderItemLayout& layout) {
    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = layout.stride();
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}

std::vector<VkVertexInputAttributeDescription> VulkanShader::get_attribute_descriptions(const ShaderItemLayout& layout) {
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
    attributeDescriptions.resize(layout.count());
    uint32_t offset = 0;
    for (uint8_t i = 0; i < layout.count(); i++) {
        attributeDescriptions[i].binding = 0;
        attributeDescriptions[i].location = i;
        attributeDescriptions[i].format = component_format(layout[i]);
        attributeDescriptions[i].offset = offset;
        offset += layout.offset(layout[i]);
    }

    return attributeDescriptions;
}

VkFormat VulkanShader::component_format(const SHADER_ITEM_COMPONENT &component) {
    switch (component) {
        case SHADER_ITEM_COMPONENT_FLOAT:
            return VK_FORMAT_R32_SFLOAT;
        case SHADER_ITEM_COMPONENT_VEC2:
            return VK_FORMAT_R32G32_SFLOAT;
        case SHADER_ITEM_COMPONENT_VEC3:
            return VK_FORMAT_R32G32B32_SFLOAT;
        default:
            return VK_FORMAT_R32G32B32A32_SFLOAT;
    }
}


VkShaderModule VulkanShader::create_shader_module(const std::vector<char> &code) {

    EG_CORE_TRACE("Creating shader module!");

    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    VK_CALL_ASSERT(vkCreateShaderModule(m_createInfo.device, &createInfo, nullptr, &shaderModule)) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

VkPipeline& VulkanShader::get_pipeline() {
    return m_graphicsPipeline;
}

VkPipelineLayout& VulkanShader::get_layout() {
    return m_pipelineLayout;
}

void VulkanShader::bind() {
    VK_CALL vkCmdBindPipeline(m_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);
}

void VulkanShader::bind_command_buffer(VkCommandBuffer cmd) {
    m_cmd = cmd;
}

void VulkanShader::compile() {
    //TODO -- implement glslang compiler
}


_EAGLE_END