//
// Created by Tom Hancocks on 23/02/2020.
//

#if !defined(DIAMANE_SHADERS_H)
#define DIAMANE_SHADERS_H

namespace diamane { namespace shader { namespace metal {

    enum vertex_input_index
    {
        vertices = 0,
        viewport_size = 1,
    };

    enum texture_index
    {
        base_color = 0,
    };

    struct vertex_descriptor
    {
    public:
        float scale;
        vector_float2 position;
        vector_float2 texture_coord;
        vector_float4 color;
    };

}}};

#endif //DIAMANE_SHADERS_H
