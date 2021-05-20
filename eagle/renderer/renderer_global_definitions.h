//
// Created by Novak on 14/07/2019.
//

#ifndef EAGLE_RENDERINGCORE_H
#define EAGLE_RENDERINGCORE_H

#include "eagle/log.h"
#include "eagle/core_global_definitions.h"

namespace eagle {

enum class DescriptorType {
    UNIFORM_BUFFER = 0,
    STORAGE_BUFFER = 1,
    SAMPLED_IMAGE = 2,
    COMBINED_IMAGE_SAMPLER = 3,
    STORAGE_IMAGE = 4
};

enum class UpdateType {
    BAKED = 0,
    DYNAMIC = 1,
};

enum TextureUsage {
    READ,
    STORAGE
};

enum class ShaderStage {
    INVALID = 0,
    VERTEX = 1,
    FRAGMENT = 2,
    COMPUTE = 3,
    GEOMETRY = 4,
    TESSALATION_CONTROL = 5,
    TESSALATION_EVALUATE = 6
};


enum class PipelineStage {
    TOP_OF_PIPE_BIT = 0x00000001,
    DRAW_INDIRECT_BIT = 0x00000002,
    VERTEX_INPUT_BIT = 0x00000004,
    VERTEX_SHADER_BIT = 0x00000008,
    TESSELLATION_CONTROL_SHADER_BIT = 0x00000010,
    TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020,
    GEOMETRY_SHADER_BIT = 0x00000040,
    FRAGMENT_SHADER_BIT = 0x00000080,
    EARLY_FRAGMENT_TESTS_BIT = 0x00000100,
    LATE_FRAGMENT_TESTS_BIT = 0x00000200,
    COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400,
    COMPUTE_SHADER_BIT = 0x00000800,
    TRANSFER_BIT = 0x00001000,
    BOTTOM_OF_PIPE_BIT = 0x00002000,
    HOST_BIT = 0x00004000,
    ALL_GRAPHICS_BIT = 0x00008000,
    ALL_COMMANDS_BIT = 0x00010000,
    TRANSFORM_FEEDBACK_BIT_EXT = 0x01000000,
    CONDITIONAL_RENDERING_BIT_EXT = 0x00040000,
    RAY_TRACING_SHADER_BIT_KHR = 0x00200000,
    ACCELERATION_STRUCTURE_BUILD_BIT_KHR = 0x02000000,
    SHADING_RATE_IMAGE_BIT_NV = 0x00400000,
    TASK_SHADER_BIT_NV = 0x00080000,
    MESH_SHADER_BIT_NV = 0x00100000,
    FRAGMENT_DENSITY_PROCESS_BIT_EXT = 0x00800000,
    COMMAND_PREPROCESS_BIT_NV = 0x00020000,
    RAY_TRACING_SHADER_BIT_NV = RAY_TRACING_SHADER_BIT_KHR,
    ACCELERATION_STRUCTURE_BUILD_BIT_NV = ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
};


enum class Filter {
    LINEAR = 1,
    NEAREST = 2
};

enum class PrimitiveTopology {
    POINT_LIST = 0,
    LINE_LIST = 1,
    LINE_STRIP = 2,
    TRIANGLE_LIST = 3,
    TRIANGLE_STRIP = 4,
    TRIANGLE_FAN = 5,
    LINE_LIST_WITH_ADJACENCY = 6,
    LINE_STRIP_WITH_ADJACENCY = 7,
    TRIANGLE_LIST_WITH_ADJACENCY = 8,
    TRIANGLE_STRIP_WITH_ADJACENCY = 9,
    PATCH_LIST = 10,
};

enum class CullMode {
    NONE = 0,
    FRONT_BIT = 1,
    BACK_BIT = 2,
    FRONT_AND_BACK = 3,
};

enum class VertexInputRate {
    VERTEX = 0,
    INSTANCE = 1
};

enum class Format{
    UNDEFINED = 0,
    R4G4_UNORM_PACK8 = 1,
    R4G4B4A4_UNORM_PACK16 = 2,
    B4G4R4A4_UNORM_PACK16 = 3,
    R5G6B5_UNORM_PACK16 = 4,
    B5G6R5_UNORM_PACK16 = 5,
    R5G5B5A1_UNORM_PACK16 = 6,
    B5G5R5A1_UNORM_PACK16 = 7,
    A1R5G5B5_UNORM_PACK16 = 8,
    R8_UNORM = 9,
    R8_SNORM = 10,
    R8_USCALED = 11,
    R8_SSCALED = 12,
    R8_UINT = 13,
    R8_SINT = 14,
    R8_SRGB = 15,
    R8G8_UNORM = 16,
    R8G8_SNORM = 17,
    R8G8_USCALED = 18,
    R8G8_SSCALED = 19,
    R8G8_UINT = 20,
    R8G8_SINT = 21,
    R8G8_SRGB = 22,
    R8G8B8_UNORM = 23,
    R8G8B8_SNORM = 24,
    R8G8B8_USCALED = 25,
    R8G8B8_SSCALED = 26,
    R8G8B8_UINT = 27,
    R8G8B8_SINT = 28,
    R8G8B8_SRGB = 29,
    B8G8R8_UNORM = 30,
    B8G8R8_SNORM = 31,
    B8G8R8_USCALED = 32,
    B8G8R8_SSCALED = 33,
    B8G8R8_UINT = 34,
    B8G8R8_SINT = 35,
    B8G8R8_SRGB = 36,
    R8G8B8A8_UNORM = 37,
    R8G8B8A8_SNORM = 38,
    R8G8B8A8_USCALED = 39,
    R8G8B8A8_SSCALED = 40,
    R8G8B8A8_UINT = 41,
    R8G8B8A8_SINT = 42,
    R8G8B8A8_SRGB = 43,
    B8G8R8A8_UNORM = 44,
    B8G8R8A8_SNORM = 45,
    B8G8R8A8_USCALED = 46,
    B8G8R8A8_SSCALED = 47,
    B8G8R8A8_UINT = 48,
    B8G8R8A8_SINT = 49,
    B8G8R8A8_SRGB = 50,
    A8B8G8R8_UNORM_PACK32 = 51,
    A8B8G8R8_SNORM_PACK32 = 52,
    A8B8G8R8_USCALED_PACK32 = 53,
    A8B8G8R8_SSCALED_PACK32 = 54,
    A8B8G8R8_UINT_PACK32 = 55,
    A8B8G8R8_SINT_PACK32 = 56,
    A8B8G8R8_SRGB_PACK32 = 57,
    A2R10G10B10_UNORM_PACK32 = 58,
    A2R10G10B10_SNORM_PACK32 = 59,
    A2R10G10B10_USCALED_PACK32 = 60,
    A2R10G10B10_SSCALED_PACK32 = 61,
    A2R10G10B10_UINT_PACK32 = 62,
    A2R10G10B10_SINT_PACK32 = 63,
    A2B10G10R10_UNORM_PACK32 = 64,
    A2B10G10R10_SNORM_PACK32 = 65,
    A2B10G10R10_USCALED_PACK32 = 66,
    A2B10G10R10_SSCALED_PACK32 = 67,
    A2B10G10R10_UINT_PACK32 = 68,
    A2B10G10R10_SINT_PACK32 = 69,
    R16_UNORM = 70,
    R16_SNORM = 71,
    R16_USCALED = 72,
    R16_SSCALED = 73,
    R16_UINT = 74,
    R16_SINT = 75,
    R16_SFLOAT = 76,
    R16G16_UNORM = 77,
    R16G16_SNORM = 78,
    R16G16_USCALED = 79,
    R16G16_SSCALED = 80,
    R16G16_UINT = 81,
    R16G16_SINT = 82,
    R16G16_SFLOAT = 83,
    R16G16B16_UNORM = 84,
    R16G16B16_SNORM = 85,
    R16G16B16_USCALED = 86,
    R16G16B16_SSCALED = 87,
    R16G16B16_UINT = 88,
    R16G16B16_SINT = 89,
    R16G16B16_SFLOAT = 90,
    R16G16B16A16_UNORM = 91,
    R16G16B16A16_SNORM = 92,
    R16G16B16A16_USCALED = 93,
    R16G16B16A16_SSCALED = 94,
    R16G16B16A16_UINT = 95,
    R16G16B16A16_SINT = 96,
    R16G16B16A16_SFLOAT = 97,
    R32_UINT = 98,
    R32_SINT = 99,
    R32_SFLOAT = 100,
    R32G32_UINT = 101,
    R32G32_SINT = 102,
    R32G32_SFLOAT = 103,
    R32G32B32_UINT = 104,
    R32G32B32_SINT = 105,
    R32G32B32_SFLOAT = 106,
    R32G32B32A32_UINT = 107,
    R32G32B32A32_SINT = 108,
    R32G32B32A32_SFLOAT = 109,
    R64_UINT = 110,
    R64_SINT = 111,
    R64_SFLOAT = 112,
    R64G64_UINT = 113,
    R64G64_SINT = 114,
    R64G64_SFLOAT = 115,
    R64G64B64_UINT = 116,
    R64G64B64_SINT = 117,
    R64G64B64_SFLOAT = 118,
    R64G64B64A64_UINT = 119,
    R64G64B64A64_SINT = 120,
    R64G64B64A64_SFLOAT = 121,
    B10G11R11_UFLOAT_PACK32 = 122,
    E5B9G9R9_UFLOAT_PACK32 = 123,
    D16_UNORM = 124,
    X8_D24_UNORM_PACK32 = 125,
    D32_SFLOAT = 126,
    S8_UINT = 127,
    D16_UNORM_S8_UINT = 128,
    D24_UNORM_S8_UINT = 129,
    D32_SFLOAT_S8_UINT = 130,
    BC1_RGB_UNORM_BLOCK = 131,
    BC1_RGB_SRGB_BLOCK = 132,
    BC1_RGBA_UNORM_BLOCK = 133,
    BC1_RGBA_SRGB_BLOCK = 134,
    BC2_UNORM_BLOCK = 135,
    BC2_SRGB_BLOCK = 136,
    BC3_UNORM_BLOCK = 137,
    BC3_SRGB_BLOCK = 138,
    BC4_UNORM_BLOCK = 139,
    BC4_SNORM_BLOCK = 140,
    BC5_UNORM_BLOCK = 141,
    BC5_SNORM_BLOCK = 142,
    BC6H_UFLOAT_BLOCK = 143,
    BC6H_SFLOAT_BLOCK = 144,
    BC7_UNORM_BLOCK = 145,
    BC7_SRGB_BLOCK = 146,
    ETC2_R8G8B8_UNORM_BLOCK = 147,
    ETC2_R8G8B8_SRGB_BLOCK = 148,
    ETC2_R8G8B8A1_UNORM_BLOCK = 149,
    ETC2_R8G8B8A1_SRGB_BLOCK = 150,
    ETC2_R8G8B8A8_UNORM_BLOCK = 151,
    ETC2_R8G8B8A8_SRGB_BLOCK = 152,
    EAC_R11_UNORM_BLOCK = 153,
    EAC_R11_SNORM_BLOCK = 154,
    EAC_R11G11_UNORM_BLOCK = 155,
    EAC_R11G11_SNORM_BLOCK = 156,
    ASTC_4x4_UNORM_BLOCK = 157,
    ASTC_4x4_SRGB_BLOCK = 158,
    ASTC_5x4_UNORM_BLOCK = 159,
    ASTC_5x4_SRGB_BLOCK = 160,
    ASTC_5x5_UNORM_BLOCK = 161,
    ASTC_5x5_SRGB_BLOCK = 162,
    ASTC_6x5_UNORM_BLOCK = 163,
    ASTC_6x5_SRGB_BLOCK = 164,
    ASTC_6x6_UNORM_BLOCK = 165,
    ASTC_6x6_SRGB_BLOCK = 166,
    ASTC_8x5_UNORM_BLOCK = 167,
    ASTC_8x5_SRGB_BLOCK = 168,
    ASTC_8x6_UNORM_BLOCK = 169,
    ASTC_8x6_SRGB_BLOCK = 170,
    ASTC_8x8_UNORM_BLOCK = 171,
    ASTC_8x8_SRGB_BLOCK = 172,
    ASTC_10x5_UNORM_BLOCK = 173,
    ASTC_10x5_SRGB_BLOCK = 174,
    ASTC_10x6_UNORM_BLOCK = 175,
    ASTC_10x6_SRGB_BLOCK = 176,
    ASTC_10x8_UNORM_BLOCK = 177,
    ASTC_10x8_SRGB_BLOCK = 178,
    ASTC_10x10_UNORM_BLOCK = 179,
    ASTC_10x10_SRGB_BLOCK = 180,
    ASTC_12x10_UNORM_BLOCK = 181,
    ASTC_12x10_SRGB_BLOCK = 182,
    ASTC_12x12_UNORM_BLOCK = 183,
    ASTC_12x12_SRGB_BLOCK = 184,
    G8B8G8R8_422_UNORM = 1000156000,
    B8G8R8G8_422_UNORM = 1000156001,
    G8_B8_R8_3PLANE_420_UNORM = 1000156002,
    G8_B8R8_2PLANE_420_UNORM = 1000156003,
    G8_B8_R8_3PLANE_422_UNORM = 1000156004,
    G8_B8R8_2PLANE_422_UNORM = 1000156005,
    G8_B8_R8_3PLANE_444_UNORM = 1000156006,
    R10X6_UNORM_PACK16 = 1000156007,
    R10X6G10X6_UNORM_2PACK16 = 1000156008,
    R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009,
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010,
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011,
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013,
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015,
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
    R12X4_UNORM_PACK16 = 1000156017,
    R12X4G12X4_UNORM_2PACK16 = 1000156018,
    R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019,
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020,
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021,
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023,
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025,
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
    G16B16G16R16_422_UNORM = 1000156027,
    B16G16R16G16_422_UNORM = 1000156028,
    G16_B16_R16_3PLANE_420_UNORM = 1000156029,
    G16_B16R16_2PLANE_420_UNORM = 1000156030,
    G16_B16_R16_3PLANE_422_UNORM = 1000156031,
    G16_B16R16_2PLANE_422_UNORM = 1000156032,
    G16_B16_R16_3PLANE_444_UNORM = 1000156033,
    PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000,
    PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001,
    PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002,
    PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003,
    PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004,
    PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005,
    PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006,
    PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007,
    G8B8G8R8_422_UNORM_KHR = G8B8G8R8_422_UNORM,
    B8G8R8G8_422_UNORM_KHR = B8G8R8G8_422_UNORM,
    G8_B8_R8_3PLANE_420_UNORM_KHR = G8_B8_R8_3PLANE_420_UNORM,
    G8_B8R8_2PLANE_420_UNORM_KHR = G8_B8R8_2PLANE_420_UNORM,
    G8_B8_R8_3PLANE_422_UNORM_KHR = G8_B8_R8_3PLANE_422_UNORM,
    G8_B8R8_2PLANE_422_UNORM_KHR = G8_B8R8_2PLANE_422_UNORM,
    G8_B8_R8_3PLANE_444_UNORM_KHR = G8_B8_R8_3PLANE_444_UNORM,
    R10X6_UNORM_PACK16_KHR = R10X6_UNORM_PACK16,
    R10X6G10X6_UNORM_2PACK16_KHR = R10X6G10X6_UNORM_2PACK16,
    R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = R10X6G10X6B10X6A10X6_UNORM_4PACK16,
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
    R12X4_UNORM_PACK16_KHR = R12X4_UNORM_PACK16,
    R12X4G12X4_UNORM_2PACK16_KHR = R12X4G12X4_UNORM_2PACK16,
    R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = R12X4G12X4B12X4A12X4_UNORM_4PACK16,
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
    G16B16G16R16_422_UNORM_KHR = G16B16G16R16_422_UNORM,
    B16G16R16G16_422_UNORM_KHR = B16G16R16G16_422_UNORM,
    G16_B16_R16_3PLANE_420_UNORM_KHR = G16_B16_R16_3PLANE_420_UNORM,
    G16_B16R16_2PLANE_420_UNORM_KHR = G16_B16R16_2PLANE_420_UNORM,
    G16_B16_R16_3PLANE_422_UNORM_KHR = G16_B16_R16_3PLANE_422_UNORM,
    G16_B16R16_2PLANE_422_UNORM_KHR = G16_B16R16_2PLANE_422_UNORM,
    G16_B16_R16_3PLANE_444_UNORM_KHR = G16_B16_R16_3PLANE_444_UNORM,
};

static uint32_t format_size(Format format){
    uint32_t result = 0;
    switch (format) {
        case Format::UNDEFINED: result = 0; break;
        case Format::R4G4_UNORM_PACK8: result = 1; break;
        case Format::R4G4B4A4_UNORM_PACK16: result = 2; break;
        case Format::B4G4R4A4_UNORM_PACK16: result = 2; break;
        case Format::R5G6B5_UNORM_PACK16: result = 2; break;
        case Format::B5G6R5_UNORM_PACK16: result = 2; break;
        case Format::R5G5B5A1_UNORM_PACK16: result = 2; break;
        case Format::B5G5R5A1_UNORM_PACK16: result = 2; break;
        case Format::A1R5G5B5_UNORM_PACK16: result = 2; break;
        case Format::R8_UNORM: result = 1; break;
        case Format::R8_SNORM: result = 1; break;
        case Format::R8_USCALED: result = 1; break;
        case Format::R8_SSCALED: result = 1; break;
        case Format::R8_UINT: result = 1; break;
        case Format::R8_SINT: result = 1; break;
        case Format::R8_SRGB: result = 1; break;
        case Format::R8G8_UNORM: result = 2; break;
        case Format::R8G8_SNORM: result = 2; break;
        case Format::R8G8_USCALED: result = 2; break;
        case Format::R8G8_SSCALED: result = 2; break;
        case Format::R8G8_UINT: result = 2; break;
        case Format::R8G8_SINT: result = 2; break;
        case Format::R8G8_SRGB: result = 2; break;
        case Format::R8G8B8_UNORM: result = 3; break;
        case Format::R8G8B8_SNORM: result = 3; break;
        case Format::R8G8B8_USCALED: result = 3; break;
        case Format::R8G8B8_SSCALED: result = 3; break;
        case Format::R8G8B8_UINT: result = 3; break;
        case Format::R8G8B8_SINT: result = 3; break;
        case Format::R8G8B8_SRGB: result = 3; break;
        case Format::B8G8R8_UNORM: result = 3; break;
        case Format::B8G8R8_SNORM: result = 3; break;
        case Format::B8G8R8_USCALED: result = 3; break;
        case Format::B8G8R8_SSCALED: result = 3; break;
        case Format::B8G8R8_UINT: result = 3; break;
        case Format::B8G8R8_SINT: result = 3; break;
        case Format::B8G8R8_SRGB: result = 3; break;
        case Format::R8G8B8A8_UNORM: result = 4; break;
        case Format::R8G8B8A8_SNORM: result = 4; break;
        case Format::R8G8B8A8_USCALED: result = 4; break;
        case Format::R8G8B8A8_SSCALED: result = 4; break;
        case Format::R8G8B8A8_UINT: result = 4; break;
        case Format::R8G8B8A8_SINT: result = 4; break;
        case Format::R8G8B8A8_SRGB: result = 4; break;
        case Format::B8G8R8A8_UNORM: result = 4; break;
        case Format::B8G8R8A8_SNORM: result = 4; break;
        case Format::B8G8R8A8_USCALED: result = 4; break;
        case Format::B8G8R8A8_SSCALED: result = 4; break;
        case Format::B8G8R8A8_UINT: result = 4; break;
        case Format::B8G8R8A8_SINT: result = 4; break;
        case Format::B8G8R8A8_SRGB: result = 4; break;
        case Format::A8B8G8R8_UNORM_PACK32: result = 4; break;
        case Format::A8B8G8R8_SNORM_PACK32: result = 4; break;
        case Format::A8B8G8R8_USCALED_PACK32: result = 4; break;
        case Format::A8B8G8R8_SSCALED_PACK32: result = 4; break;
        case Format::A8B8G8R8_UINT_PACK32: result = 4; break;
        case Format::A8B8G8R8_SINT_PACK32: result = 4; break;
        case Format::A8B8G8R8_SRGB_PACK32: result = 4; break;
        case Format::A2R10G10B10_UNORM_PACK32: result = 4; break;
        case Format::A2R10G10B10_SNORM_PACK32: result = 4; break;
        case Format::A2R10G10B10_USCALED_PACK32: result = 4; break;
        case Format::A2R10G10B10_SSCALED_PACK32: result = 4; break;
        case Format::A2R10G10B10_UINT_PACK32: result = 4; break;
        case Format::A2R10G10B10_SINT_PACK32: result = 4; break;
        case Format::A2B10G10R10_UNORM_PACK32: result = 4; break;
        case Format::A2B10G10R10_SNORM_PACK32: result = 4; break;
        case Format::A2B10G10R10_USCALED_PACK32: result = 4; break;
        case Format::A2B10G10R10_SSCALED_PACK32: result = 4; break;
        case Format::A2B10G10R10_UINT_PACK32: result = 4; break;
        case Format::A2B10G10R10_SINT_PACK32: result = 4; break;
        case Format::R16_UNORM: result = 2; break;
        case Format::R16_SNORM: result = 2; break;
        case Format::R16_USCALED: result = 2; break;
        case Format::R16_SSCALED: result = 2; break;
        case Format::R16_UINT: result = 2; break;
        case Format::R16_SINT: result = 2; break;
        case Format::R16_SFLOAT: result = 2; break;
        case Format::R16G16_UNORM: result = 4; break;
        case Format::R16G16_SNORM: result = 4; break;
        case Format::R16G16_USCALED: result = 4; break;
        case Format::R16G16_SSCALED: result = 4; break;
        case Format::R16G16_UINT: result = 4; break;
        case Format::R16G16_SINT: result = 4; break;
        case Format::R16G16_SFLOAT: result = 4; break;
        case Format::R16G16B16_UNORM: result = 6; break;
        case Format::R16G16B16_SNORM: result = 6; break;
        case Format::R16G16B16_USCALED: result = 6; break;
        case Format::R16G16B16_SSCALED: result = 6; break;
        case Format::R16G16B16_UINT: result = 6; break;
        case Format::R16G16B16_SINT: result = 6; break;
        case Format::R16G16B16_SFLOAT: result = 6; break;
        case Format::R16G16B16A16_UNORM: result = 8; break;
        case Format::R16G16B16A16_SNORM: result = 8; break;
        case Format::R16G16B16A16_USCALED: result = 8; break;
        case Format::R16G16B16A16_SSCALED: result = 8; break;
        case Format::R16G16B16A16_UINT: result = 8; break;
        case Format::R16G16B16A16_SINT: result = 8; break;
        case Format::R16G16B16A16_SFLOAT: result = 8; break;
        case Format::R32_UINT: result = 4; break;
        case Format::R32_SINT: result = 4; break;
        case Format::R32_SFLOAT: result = 4; break;
        case Format::R32G32_UINT: result = 8; break;
        case Format::R32G32_SINT: result = 8; break;
        case Format::R32G32_SFLOAT: result = 8; break;
        case Format::R32G32B32_UINT: result = 12; break;
        case Format::R32G32B32_SINT: result = 12; break;
        case Format::R32G32B32_SFLOAT: result = 12; break;
        case Format::R32G32B32A32_UINT: result = 16; break;
        case Format::R32G32B32A32_SINT: result = 16; break;
        case Format::R32G32B32A32_SFLOAT: result = 16; break;
        case Format::R64_UINT: result = 8; break;
        case Format::R64_SINT: result = 8; break;
        case Format::R64_SFLOAT: result = 8; break;
        case Format::R64G64_UINT: result = 16; break;
        case Format::R64G64_SINT: result = 16; break;
        case Format::R64G64_SFLOAT: result = 16; break;
        case Format::R64G64B64_UINT: result = 24; break;
        case Format::R64G64B64_SINT: result = 24; break;
        case Format::R64G64B64_SFLOAT: result = 24; break;
        case Format::R64G64B64A64_UINT: result = 32; break;
        case Format::R64G64B64A64_SINT: result = 32; break;
        case Format::R64G64B64A64_SFLOAT: result = 32; break;
        case Format::B10G11R11_UFLOAT_PACK32: result = 4; break;
        case Format::E5B9G9R9_UFLOAT_PACK32: result = 4; break;
        default:
        EG_WARNING("eagle", "Unknown format size! default to 0");
        break;
    }
    return result;
}

enum class AttachmentLoadOperator {
    LOAD = 0,
    CLEAR = 1,
    DONT_CARE = 2
};

enum class AttachmentStoreOperator {
    STORE = 0,
    DONT_CARE = 1,
    NONE_QCOM = 1000301000
};

enum class ImageLayout {
    UNDEFINED = 0,
    GENERAL = 1,
    COLOR_ATTACHMENT_OPTIMAL = 2,
    DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
    DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
    SHADER_READ_ONLY_OPTIMAL = 5,
    TRANSFER_SRC_OPTIMAL = 6,
    TRANSFER_DST_OPTIMAL = 7,
    PREINITIALIZED = 8,
    DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL = 1000117000,
    DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL = 1000117001,
    PRESENT_SRC_KHR = 1000001002,
    SHARED_PRESENT_KHR = 1000111000,
    SHADING_RATE_OPTIMAL_NV = 1000164003,
    FRAGMENT_DENSITY_MAP_OPTIMAL_EXT = 1000218000
};

enum class ImageTiling {
    OPTIMAL = 0,
    LINEAR = 1,
    DRM_FORMAT_MODIFIER_EXT = 1000158000
};

enum class ImageType {
    D1 = 0,//unsupported
    D2 = 1,
    D3 = 2,//unsupported
    CUBE = 3,
    D1_ARRAY = 4,//unsupported
    D2_ARRAY = 5,//unsupported
    CUBE_ARRAY = 6,//unsupported
};

enum class ImageUsage {
    TRANSFER_SRC = 0x00000001,
    TRANSFER_DST = 0x00000002,
    SAMPLED = 0x00000004,
    STORAGE = 0x00000008,
    COLOR_ATTACHMENT = 0x00000010,
    DEPTH_STENCIL_ATTACHMENT = 0x00000020,
    TRANSIENT_ATTACHMENT = 0x00000040,
    INPUT_ATTACHMENT = 0x00000080,
    SHADING_RATE_IMAGE_NV = 0x00000100,
    FRAGMENT_DENSITY_MAP_EXT = 0x00000200
};

enum class MemoryProperty {
    DEVICE_LOCAL = 0x00000001,
    HOST_VISIBLE = 0x00000002,
    HOST_COHERENT = 0x00000004,
    HOST_CACHED = 0x00000008,
    LAZILY_ALLOCATED = 0x00000010,
    PROTECTED = 0x00000020,
    DEVICE_COHERENT_AMD = 0x00000040,
    DEVICE_UNCACHED_AMD = 0x00000080
};

enum class ImageAspect {
    COLOR = 0x00000001,
    DEPTH = 0x00000002,
    STENCIL = 0x00000004,
    METADATA = 0x00000008,
    PLANE_0 = 0x00000010,
    PLANE_1 = 0x00000020,
    PLANE_2 = 0x00000040,
    MEMORY_PLANE_0_EXT = 0x00000080,
    MEMORY_PLANE_1_EXT = 0x00000100,
    MEMORY_PLANE_2_EXT = 0x00000200,
    MEMORY_PLANE_3_EXT = 0x00000400,
    PLANE_0_KHR = PLANE_0,
    PLANE_1_KHR = PLANE_1,
    PLANE_2_KHR = PLANE_2
};

}

#endif //EAGLE_RENDERINGCORE_H
