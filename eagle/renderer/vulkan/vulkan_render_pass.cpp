//
// Created by Ricardo on 10/24/2020.
//

#include <eagle/renderer/vulkan/vulkan_render_pass.h>
#include <eagle/renderer/vulkan/vulkan_converter.h>

namespace eagle {

VulkanRenderPass::VulkanRenderPass(
        RenderPassCreateInfo createInfo,
        const VulkanRenderPassCreateInfo& vulkanCreateInfo) :
        RenderPass(std::move(createInfo)),
        m_vulkanCreateInfo(vulkanCreateInfo) {
    EG_TRACE("eagle","Creating a VulkanRenderPass!");
    m_vkColorAttachments = std::move(VulkanConverter::to_vk_vector<VkAttachmentDescription>(m_createInfo.colorAttachments));
    m_vkDepthAttachment = VulkanConverter::to_vk(m_createInfo.depthAttachment);

    m_clearValues.resize(m_vkColorAttachments.size());
    std::for_each(m_clearValues.begin(), m_clearValues.end(), [](VkClearValue& value){
        value.color = {0.0f, 0.0f, 0.0f, 1.0f};
    });
    VkClearValue depthClearValues = {};
    depthClearValues.depthStencil = {1.0f, 0};
    m_clearValues.emplace_back(depthClearValues);

    create_native_render_pass();
    EG_TRACE("eagle","VulkanRenderPass created!");
}

void VulkanRenderPass::create_native_render_pass() {
    EG_TRACE("eagle","Creating a native render pass!");

    std::vector<VkAttachmentReference> colorAttachmentRefs;
    colorAttachmentRefs.reserve(m_vkColorAttachments.size());
    for (int i = 0; i < m_vkColorAttachments.size(); i++){
        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = i;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        colorAttachmentRefs.emplace_back(colorAttachmentRef);
    }

    VkAttachmentReference depthAttachmentRef = {};
    depthAttachmentRef.attachment = colorAttachmentRefs.size();
    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = colorAttachmentRefs.size();
    subpass.pColorAttachments = colorAttachmentRefs.data();
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    std::array<VkSubpassDependency, 2> dependencies = {};
    dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[0].dstSubpass = 0;
    dependencies[0].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].srcAccessMask = 0;
    dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    dependencies[1].srcSubpass = 0;
    dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;


    std::vector<VkAttachmentDescription> attachments(m_vkColorAttachments);
    attachments.emplace_back(m_vkDepthAttachment);

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = attachments.size();
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = dependencies.size();
    renderPassInfo.pDependencies = dependencies.data();

    VK_CALL_ASSERT(vkCreateRenderPass(m_vulkanCreateInfo.device, &renderPassInfo, nullptr, &m_vkRenderPass)) {
        throw std::runtime_error("failed to create render pass!");
    }

    EG_TRACE("eagle","Native render pass created!");
}

VulkanRenderPass::~VulkanRenderPass() {
    EG_TRACE("eagle","Destroying a VulkanRenderPass!");
    cleanup();
    EG_TRACE("eagle","VulkanRenderPass destroyed!");
}

void VulkanRenderPass::cleanup() {
    EG_TRACE("eagle","Cleaning up a VulkanRenderPass!");
    VK_CALL vkDestroyRenderPass(m_vulkanCreateInfo.device, m_vkRenderPass, nullptr);
    EG_TRACE("eagle","VulkanRenderPass cleaned!");
}

}
