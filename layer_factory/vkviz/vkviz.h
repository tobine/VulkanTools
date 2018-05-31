/* Copyright (C) 2018 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Tobin Ehlis <tobine@google.com>
 */

#pragma once

#include <unordered_map>
#include <iostream>
#include <fstream>

// vkCmd tracking -- complete as of header 1.0.68
// please keep in "none, then sorted" order
// Note: grepping vulkan.h for VKAPI_CALL.*vkCmd will return all functions except vkEndCommandBuffer

enum CMD_TYPE {
    CMD_NONE,
    CMD_BEGINCOMMANDBUFFER, // Should be the first command
    CMD_BEGINDEBUGUTILSLABELEXT,
    CMD_BEGINQUERY,
    CMD_BEGINRENDERPASS,
    CMD_BINDDESCRIPTORSETS,
    CMD_BINDINDEXBUFFER,
    CMD_BINDPIPELINE,
    CMD_BINDVERTEXBUFFERS,
    CMD_BLITIMAGE,
    CMD_CLEARATTACHMENTS,
    CMD_CLEARCOLORIMAGE,
    CMD_CLEARDEPTHSTENCILIMAGE,
    CMD_COPYBUFFER,
    CMD_COPYBUFFERTOIMAGE,
    CMD_COPYIMAGE,
    CMD_COPYIMAGETOBUFFER,
    CMD_COPYQUERYPOOLRESULTS,
    CMD_DEBUGMARKERBEGINEXT,
    CMD_DEBUGMARKERENDEXT,
    CMD_DEBUGMARKERINSERTEXT,
    CMD_DISPATCH,
    CMD_DISPATCHBASE,
    CMD_DISPATCHBASEKHR,
    CMD_DISPATCHINDIRECT,
    CMD_DRAW,
    CMD_DRAWINDEXED,
    CMD_DRAWINDEXEDINDIRECT,
    CMD_DRAWINDEXEDINDIRECTCOUNTAMD,
    CMD_DRAWINDIRECT,
    CMD_DRAWINDIRECTCOUNTAMD,
    CMD_ENDCOMMANDBUFFER,  // Should be the last command in any RECORDED cmd buffer
    CMD_ENDDEBUGUTILSLABELEXT,
    CMD_ENDQUERY,
    CMD_ENDRENDERPASS,
    CMD_EXECUTECOMMANDS,
    CMD_FILLBUFFER,
    CMD_INSERTDEBUGUTILSLABELEXT,
    CMD_NEXTSUBPASS,
    CMD_PIPELINEBARRIER,
    CMD_PROCESSCOMMANDSNVX,
    CMD_PUSHCONSTANTS,
    CMD_PUSHDESCRIPTORSETKHR,
    CMD_PUSHDESCRIPTORSETWITHTEMPLATEKHR,
    CMD_RESERVESPACEFORCOMMANDSNVX,
    CMD_RESETEVENT,
    CMD_RESETQUERYPOOL,
    CMD_RESOLVEIMAGE,
    CMD_SETBLENDCONSTANTS,
    CMD_SETDEPTHBIAS,
    CMD_SETDEPTHBOUNDS,
    CMD_SETDEVICEMASK,
    CMD_SETDEVICEMASKKHR,
    CMD_SETDISCARDRECTANGLEEXT,
    CMD_SETEVENT,
    CMD_SETLINEWIDTH,
    CMD_SETSAMPLELOCATIONSEXT,
    CMD_SETSCISSOR,
    CMD_SETSTENCILCOMPAREMASK,
    CMD_SETSTENCILREFERENCE,
    CMD_SETSTENCILWRITEMASK,
    CMD_SETVIEWPORT,
    CMD_SETVIEWPORTWSCALINGNV,
    CMD_UPDATEBUFFER,
    CMD_WAITEVENTS,
    CMD_WRITEBUFFERMARKERAMD,
    CMD_WRITETIMESTAMP,
};

std::string cmdToString(CMD_TYPE cmd) {
    switch(cmd) {
        CMD_NONE:
            return "CMD_NONE";
        CMD_BEGINCOMMANDBUFFER: // Should be the first command
            return "CMD_BEGINCOMMANDBUFFER";
        CMD_BEGINDEBUGUTILSLABELEXT:
            return "CMD_BEGINDEBUGUTILSLABELEXT";
        CMD_BEGINQUERY:
            return "CMD_BEGINQUERY";
        CMD_BEGINRENDERPASS:
            return "CMD_BEGINRENDERPASS";
        CMD_BINDDESCRIPTORSETS:
            return "CMD_BINDDESCRIPTORSETS";
        CMD_BINDINDEXBUFFER:
            return "CMD_BINDINDEXBUFFER";
        CMD_BINDPIPELINE:
            return "CMD_BINDPIPELINE";
        CMD_BINDVERTEXBUFFERS:
            return "CMD_BINDVERTEXBUFFERS";
        CMD_BLITIMAGE:
            return "CMD_BLITIMAGE";
        CMD_CLEARATTACHMENTS:
            return "CMD_CLEARATTACHMENTS";
        CMD_CLEARCOLORIMAGE:
            return "CMD_CLEARCOLORIMAGE";
        CMD_CLEARDEPTHSTENCILIMAGE:
            return "CMD_CLEARDEPTHSTENCILIMAGE";
        CMD_COPYBUFFER:
            return "CMD_COPYBUFFER";
        CMD_COPYBUFFERTOIMAGE:
            return "CMD_COPYBUFFERTOIMAGE";
        CMD_COPYIMAGE:
            return "CMD_COPYIMAGE";
        CMD_COPYIMAGETOBUFFER:
            return "CMD_COPYIMAGETOBUFFER";
        CMD_COPYQUERYPOOLRESULTS:
            return "CMD_COPYQUERYPOOLRESULTS";
        CMD_DEBUGMARKERBEGINEXT:
            return "CMD_DEBUGMARKERBEGINEXT";
        CMD_DEBUGMARKERENDEXT:
            return "CMD_DEBUGMARKERENDEXT";
        CMD_DEBUGMARKERINSERTEXT:
            return "CMD_DEBUGMARKERINSERTEXT";
        CMD_DISPATCH:
            return "CMD_DISPATCH";
        CMD_DISPATCHBASE:
            return "CMD_DISPATCHBASE";
        CMD_DISPATCHBASEKHR:
            return "CMD_DISPATCHBASEKHR";
        CMD_DISPATCHINDIRECT:
            return "CMD_DISPATCHINDIRECT";
        CMD_DRAW:
            return "CMD_DRAW";
        CMD_DRAWINDEXED:
            return "CMD_DRAWINDEXED";
        CMD_DRAWINDEXEDINDIRECT:
            return "CMD_DRAWINDEXEDINDIRECT";
        CMD_DRAWINDEXEDINDIRECTCOUNTAMD:
            return "CMD_DRAWINDEXEDINDIRECTCOUNTAMD";
        CMD_DRAWINDIRECT:
            return "CMD_DRAWINDIRECT";
        CMD_DRAWINDIRECTCOUNTAMD:
            return "CMD_DRAWINDIRECTCOUNTAMD";
        CMD_ENDCOMMANDBUFFER: // Should be the last command in any RECORDED cmd buffer
            return "CMD_ENDCOMMANDBUFFER";
        CMD_ENDDEBUGUTILSLABELEXT:
            return "CMD_ENDDEBUGUTILSLABELEXT";
        CMD_ENDQUERY:
            return "CMD_ENDQUERY";
        CMD_ENDRENDERPASS:
            return "CMD_ENDRENDERPASS";
        CMD_EXECUTECOMMANDS:
            return "CMD_EXECUTECOMMANDS";
        CMD_FILLBUFFER:
            return "CMD_FILLBUFFER";
        CMD_INSERTDEBUGUTILSLABELEXT:
            return "CMD_INSERTDEBUGUTILSLABELEXT";
        CMD_NEXTSUBPASS:
            return "CMD_NEXTSUBPASS";
        CMD_PIPELINEBARRIER:
            return "CMD_PIPELINEBARRIER";
        CMD_PROCESSCOMMANDSNVX:
            return "CMD_PROCESSCOMMANDSNVX";
        CMD_PUSHCONSTANTS:
            return "CMD_PUSHCONSTANTS";
        CMD_PUSHDESCRIPTORSETKHR:
            return "CMD_PUSHDESCRIPTORSETKHR";
        CMD_PUSHDESCRIPTORSETWITHTEMPLATEKHR:
            return "CMD_PUSHDESCRIPTORSETWITHTEMPLATEKHR";
        CMD_RESERVESPACEFORCOMMANDSNVX:
            return "CMD_RESERVESPACEFORCOMMANDSNVX";
        CMD_RESETEVENT:
            return "CMD_RESETEVENT";
        CMD_RESETQUERYPOOL:
            return "CMD_RESETQUERYPOOL";
        CMD_RESOLVEIMAGE:
            return "CMD_RESOLVEIMAGE";
        CMD_SETBLENDCONSTANTS:
            return "CMD_SETBLENDCONSTANTS";
        CMD_SETDEPTHBIAS:
            return "CMD_SETDEPTHBIAS";
        CMD_SETDEPTHBOUNDS:
            return "CMD_SETDEPTHBOUNDS";
        CMD_SETDEVICEMASK:
            return "CMD_SETDEVICEMASK";
        CMD_SETDEVICEMASKKHR:
            return "CMD_SETDEVICEMASKKHR";
        CMD_SETDISCARDRECTANGLEEXT:
            return "CMD_SETDISCARDRECTANGLEEXT";
        CMD_SETEVENT:
            return "CMD_SETEVENT";
        CMD_SETLINEWIDTH:
            return "CMD_SETLINEWIDTH";
        CMD_SETSAMPLELOCATIONSEXT:
            return "CMD_SETSAMPLELOCATIONSEXT";
        CMD_SETSCISSOR:
            return "CMD_SETSCISSOR";
        CMD_SETSTENCILCOMPAREMASK:
            return "CMD_SETSTENCILCOMPAREMASK";
        CMD_SETSTENCILREFERENCE:
            return "CMD_SETSTENCILREFERENCE";
        CMD_SETSTENCILWRITEMASK:
            return "CMD_SETSTENCILWRITEMASK";
        CMD_SETVIEWPORT:
            return "CMD_SETVIEWPORT";
        CMD_SETVIEWPORTWSCALINGNV:
            return "CMD_SETVIEWPORTWSCALINGNV";
        CMD_UPDATEBUFFER:
            return "CMD_UPDATEBUFFER";
        CMD_WAITEVENTS:
            return "CMD_WAITEVENTS";
        CMD_WRITEBUFFERMARKERAMD:
            return "CMD_WRITEBUFFERMARKERAMD";
        CMD_WRITETIMESTAMP:
            return "CMD_WRITETIMESTAMP";
        default:
            return "CMD_UNKNOWN";
    }
};

class CommandWrapper {
   public:
    CommandWrapper() : type(CMD_NONE){};
    CommandWrapper(CMD_TYPE t) : type(t){};
    CMD_TYPE type;
};

class VkViz : public layer_factory {
   public:
    // Constructor for interceptor
    VkViz() : layer_factory(this), outfile_num_(0), outfile_base_name_("vkviz_out"){};

    VkResult PostCallBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BEGINCOMMANDBUFFER);
    }
    VkResult PostCallEndCommandBuffer(VkCommandBuffer commandBuffer) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_ENDCOMMANDBUFFER);
    }
    void PostCallCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BEGINDEBUGUTILSLABELEXT);
    }
    void PostCallCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BEGINQUERY);
    }
    void PostCallCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BEGINRENDERPASS);
    }
    void PostCallCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BINDDESCRIPTORSETS);
    }
    void PostCallCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BINDINDEXBUFFER);
    }
    void PostCallCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BINDPIPELINE);
    }
    void PostCallCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BINDVERTEXBUFFERS);
    }
    void PostCallCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_BLITIMAGE);
    }
    void PostCallCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_CLEARATTACHMENTS);
    }
    void PostCallCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_CLEARCOLORIMAGE);
    }
    void PostCallCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_CLEARDEPTHSTENCILIMAGE);
    }
    void PostCallCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_COPYBUFFER);
    }
    void PostCallCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_COPYBUFFERTOIMAGE);
    }
    void PostCallCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_COPYIMAGE);
    }
    void PostCallCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_COPYIMAGETOBUFFER);
    }
    void PostCallCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_COPYQUERYPOOLRESULTS);
    }
    void PostCallCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DEBUGMARKERBEGINEXT);
    }
    void PostCallCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DEBUGMARKERENDEXT);
    }
    void PostCallCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DEBUGMARKERINSERTEXT);
    }
    void PostCallCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DISPATCH);
    }
    void PostCallCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DISPATCHBASE);
    }
    void PostCallCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DISPATCHBASEKHR);
    }
    void PostCallCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DISPATCHINDIRECT);
    }
    void PostCallCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DRAW);
    }
    void PostCallCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DRAWINDEXED);
    }
    void PostCallCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DRAWINDEXEDINDIRECT);
    }
    void PostCallCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DRAWINDEXEDINDIRECTCOUNTAMD);
    }
    void PostCallCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DRAWINDIRECT);
    }
    void PostCallCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_DRAWINDIRECTCOUNTAMD);
    }
    void PostCallCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_ENDDEBUGUTILSLABELEXT);
    }
    void PostCallCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_ENDQUERY);
    }
    void PostCallCmdEndRenderPass(VkCommandBuffer commandBuffer) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_ENDRENDERPASS);
    }
    void PostCallCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_EXECUTECOMMANDS);
    }
    void PostCallCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_FILLBUFFER);
    }
    void PostCallCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_INSERTDEBUGUTILSLABELEXT);
    }
    void PostCallCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_NEXTSUBPASS);
    }
    void PostCallCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_PIPELINEBARRIER);
    }
    void PostCallCmdProcessCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdProcessCommandsInfoNVX* pProcessCommandsInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_PROCESSCOMMANDSNVX);
    }
    void PostCallCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_PUSHCONSTANTS);
    }
    void PostCallCmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_PUSHDESCRIPTORSETKHR);
    }
    void PostCallCmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_PUSHDESCRIPTORSETWITHTEMPLATEKHR);
    }
    void PostCallCmdReserveSpaceForCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdReserveSpaceForCommandsInfoNVX* pReserveSpaceInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_RESERVESPACEFORCOMMANDSNVX);
    }
    void PostCallCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_RESETEVENT);
    }
    void PostCallCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_RESETQUERYPOOL);
    }
    void PostCallCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_RESOLVEIMAGE);
    }
    void PostCallCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETBLENDCONSTANTS);
    }
    void PostCallCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETDEPTHBIAS);
    }
    void PostCallCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETDEPTHBOUNDS);
    }
    void PostCallCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETDEVICEMASK);
    }
    void PostCallCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETDEVICEMASKKHR);
    }
    void PostCallCmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETDISCARDRECTANGLEEXT);
    }
    void PostCallCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETEVENT);
    }
    void PostCallCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETLINEWIDTH);
    }
    void PostCallCmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETSAMPLELOCATIONSEXT);
    }
    void PostCallCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETSCISSOR);
    }
    void PostCallCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETSTENCILCOMPAREMASK);
    }
    void PostCallCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETSTENCILREFERENCE);
    }
    void PostCallCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETSTENCILWRITEMASK);
    }
    void PostCallCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETVIEWPORT);
    }
    void PostCallCmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_SETVIEWPORTWSCALINGNV);
    }
    void PostCallCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_UPDATEBUFFER);
    }
    void PostCallCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_WAITEVENTS);
    }
    void PostCallCmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_WRITEBUFFERMARKERAMD);
    }
    void PostCallCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
        cmdbuffer_map_[commandBuffer].push_back(CMD_WRITETIMESTAMP);
    }
    VkResult PostCallQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) {
        // Write dot file with cmd buffers for each submit
        uint32_t node_num = 0;
        std::string filename = outfile_base_name_ + std::to_string(outfile_num_) + ".dot";
        outfile_.open(filename);
        // Write graphviz of cmd buffers
        outfile_ << "digraph G {\n  node [shape=record];\n";
        for (uint32_t i = 0; i < submitCount; ++i) {
            for (uint32_t j = 0; j < pSubmits[i].commandBufferCount; ++j) {
                outfile_ << "  node" << node_num << "[ label = \"{<n> COMMAND BUFFER 0x" << pSubmits[i].pCommandBuffers[j] << " ";
                for (const auto &cmd : cmdbuffer_map_[pSubmits[i].pCommandBuffers[j]]) {
                    outfile_ << "| " << cmdToString(cmd);
                }
                outfile_ << "];\n";
            }
        }
        outfile_ << "}";
        outfile_.close();
    }
   private:
    //
    std::unordered_map<VkCommandBuffer, std::vector<CMD_TYPE>> cmdbuffer_map_;
    std::ofstream outfile_;
    uint32_t outfile_num_;
    std::string outfile_base_name_;
};
