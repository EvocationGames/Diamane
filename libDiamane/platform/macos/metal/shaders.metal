//
// Created by Tom Hancocks on 23/02/2020.
//

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

// Include header shared between this Metal shader code and C code executing Metal API commands
#include "libDiamane/platform/macos/metal/shaders.h"

typedef struct
{
    float4 position [[position]];
    float4 color;
    float2 texture_coord;

} rasterizer_data;

// Vertex Function
vertex rasterizer_data vertexShader(
    uint vertex_id [[ vertex_id ]],
	constant diamane::shader::metal::vertex_descriptor *vertex_array [[ buffer(diamane::shader::metal::vertex_input_index::vertices) ]],
	constant vector_uint2 *viewport_size_pointer [[ buffer(diamane::shader::metal::vertex_input_index::viewport_size) ]]
) {

    rasterizer_data out;

    float2 pixel_space_position = vertex_array[vertex_id].position.xy;
    float2 viewport_size = float2(*viewport_size_pointer);

    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixel_space_position / (viewport_size / vertex_array[vertex_id].scale);
    out.texture_coord = vertex_array[vertex_id].texture_coord;
    out.color = vertex_array[vertex_id].color;

    return out;
}

// Fragment function
fragment float4 samplingShader(
    rasterizer_data in [[stage_in]],
	texture2d<half> color_texture [[ texture(diamane::shader::metal::texture_index::base_color) ]]
) {
    constexpr sampler texture_sampler (mag_filter::linear, min_filter::linear);
    const float4 color_sample = in.color * float4(color_texture.sample(texture_sampler, in.texture_coord));
    return color_sample;
}
