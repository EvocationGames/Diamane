//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__

#include "libDiamane/platform/macos/metal/metalgraphics.h"
#include "libDiamane/platform/macos/metal/metalgraphicsview.h"
#include "libDiamane/platform/macos/metal/shaders.h"
#include "libDiamane/graphics/color.hpp"
#include <array>

@import simd;

static inline auto color_vector(const diamane::gl::color& c) -> simd_float4
{
    return vector4(static_cast<float>(c.red()),
                   static_cast<float>(c.green()),
                   static_cast<float>(c.blue()),
                   static_cast<float>(c.alpha()));
}

@implementation MetalGraphics {
    id <MTLDevice> _device;
    id <MTLCommandQueue> _commandQueue;
    id <MTLRenderCommandEncoder> _commandEncoder;
    vector_uint2 _viewportSize;
    NSMutableArray<id<MTLTexture>> *_textures;
    NSMutableArray<id<MTLRenderPipelineState>> *_pipelineStates;
    MetalGraphicsView *_graphicsView;
}

// MARK: - Instance Setup

+ (instancetype)graphicsForView:(MetalGraphicsView *)graphicsView usingDevice:(id<MTLDevice>)device
{
    return [[self alloc] initWithView:graphicsView usingDevice:device];
}

- (instancetype)initWithView:(MetalGraphicsView *)graphicsView usingDevice:(id<MTLDevice>)device
{
    if (self = [super init]) {
        _graphicsView = graphicsView;
        [_graphicsView setDevice:device];
        _device = device;
        [_graphicsView setDelegate:self];

        // Configure Metal Library
        NSError *error = nil;
        NSString *libraryFile = [[NSBundle mainBundle] pathForResource:@"diamane" ofType:@"metallib"];
        id <MTLLibrary> library = [_device newLibraryWithFile:libraryFile error:&error];
        if (!library) {
            throw std::runtime_error("Failed to load underlying metal library");
        }

        // Configure Metal render pipelines
        _pipelineStates = [[NSMutableArray alloc] initWithCapacity:2];
        [self buildPipelineStateForNormalBlendModeUsingLibrary:library];
        [self buildPipelineStateForLightBlendModeUsingLibrary:library];

        // Request a new command queue.
        _commandQueue = [_device newCommandQueue];
    }
    return self;
}

// MARK: - Accessors

- (vector_uint2 *)viewportSize
{
    return &_viewportSize;
}

- (id<MTLRenderCommandEncoder>)commandEncoder
{
    return _commandEncoder;
}

- (float)nativeScale
{
    return (float)[[[_graphicsView window] screen] backingScaleFactor];
}

// MARK: - Pipelines


- (void)buildPipelineStateForNormalBlendModeUsingLibrary:(id <MTLLibrary>)library
{
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_enter(group);

    MTLRenderPipelineDescriptor *pipeline = [[MTLRenderPipelineDescriptor alloc] init];
    [pipeline setLabel:@"com.diamane.pipeline.normal"];
    [pipeline setVertexFunction:[library newFunctionWithName:@"vertexShader"]];
    [pipeline setFragmentFunction:[library newFunctionWithName:@"samplingShader"]];
    [[pipeline colorAttachments][0] setPixelFormat:[_graphicsView colorPixelFormat]];
    [[pipeline colorAttachments][0] setBlendingEnabled:YES];
    [[pipeline colorAttachments][0] setRgbBlendOperation:MTLBlendOperationAdd];
    [[pipeline colorAttachments][0] setAlphaBlendOperation:MTLBlendOperationAdd];
    [[pipeline colorAttachments][0] setSourceRGBBlendFactor:MTLBlendFactorSourceAlpha];
    [[pipeline colorAttachments][0] setSourceAlphaBlendFactor:MTLBlendFactorSourceAlpha];
    [[pipeline colorAttachments][0] setDestinationRGBBlendFactor:MTLBlendFactorOneMinusSourceAlpha];
    [[pipeline colorAttachments][0] setDestinationAlphaBlendFactor:MTLBlendFactorOneMinusSourceAlpha];

    [_device newRenderPipelineStateWithDescriptor:pipeline completionHandler:^(id<MTLRenderPipelineState> renderPipelineState, NSError *error) {
        [self->_pipelineStates addObject:renderPipelineState];
        dispatch_group_leave(group);
    }];

    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
}

- (void)buildPipelineStateForLightBlendModeUsingLibrary:(id <MTLLibrary>)library
{
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_enter(group);

    MTLRenderPipelineDescriptor *pipeline = [[MTLRenderPipelineDescriptor alloc] init];
    [pipeline setLabel:@"com.diamane.pipeline.light"];
    [pipeline setVertexFunction:[library newFunctionWithName:@"vertexShader"]];
    [pipeline setFragmentFunction:[library newFunctionWithName:@"samplingShader"]];
    [[pipeline colorAttachments][0] setPixelFormat:[_graphicsView colorPixelFormat]];
    [[pipeline colorAttachments][0] setBlendingEnabled:YES];
    [[pipeline colorAttachments][0] setRgbBlendOperation:MTLBlendOperationAdd];
    [[pipeline colorAttachments][0] setAlphaBlendOperation:MTLBlendOperationAdd];
    [[pipeline colorAttachments][0] setSourceRGBBlendFactor:MTLBlendFactorSourceAlpha];
    [[pipeline colorAttachments][0] setSourceAlphaBlendFactor:MTLBlendFactorSourceAlpha];
    [[pipeline colorAttachments][0] setDestinationRGBBlendFactor:MTLBlendFactorOne];
    [[pipeline colorAttachments][0] setDestinationAlphaBlendFactor:MTLBlendFactorOneMinusSourceAlpha];

    [_device newRenderPipelineStateWithDescriptor:pipeline completionHandler:^(id<MTLRenderPipelineState> renderPipelineState, NSError *error) {
        [self->_pipelineStates addObject:renderPipelineState];
        dispatch_group_leave(group);
    }];

    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
}

- (void)restorePipelineState
{
    [_commandEncoder setRenderPipelineState:_pipelineStates[0]];
}

- (void)setPipelineStateForIndex:(int)index
{
    [_commandEncoder setRenderPipelineState:_pipelineStates[index]];
}

// MARK: - Metal View Delegate

- (void)drawInMTKView:(MTKView *)view
{
    id <MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];

    [_graphicsView frameStart];

    // Setup a new render pass and prepare to render a new frame.
    MTLRenderPassDescriptor *renderPass = [view currentRenderPassDescriptor];
    if (renderPass) {
        MTLViewport viewport;
        viewport.originX = 0.0;
        viewport.originY = 0.0;
        viewport.width = _viewportSize.x;
        viewport.height = _viewportSize.y;
        viewport.znear = 1.0;
        viewport.zfar = -1.0;

        _commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPass];
        [_commandEncoder setLabel:@"com.diamane.render-encoder"];
        [_commandEncoder setViewport:viewport];
        [_commandEncoder setRenderPipelineState:_pipelineStates[0]];

        [_graphicsView frameDraw];

        [_commandEncoder endEncoding];
        _commandEncoder = nil;

        [commandBuffer presentDrawable:[view currentDrawable]];
    }

    // Commit the drawing commands and finish the frame.
    [commandBuffer commit];

    [_graphicsView frameEnd];
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
    _viewportSize.x = size.width;
    _viewportSize.y = size.height;
}

// MARK: - Texture Management

- (void)registerTexture:(std::shared_ptr<diamane::gl::texture>)texture
{
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];
    [textureDescriptor setPixelFormat:MTLPixelFormatRGBA8Unorm];

    // Set the dimensions of the texture
    auto size = texture->size();
    [textureDescriptor setWidth:(NSUInteger)(size.width())];
    [textureDescriptor setHeight:(NSUInteger)(size.height())];

    // Create the texture from the device using the descriptor
    id <MTLTexture> mtlTexture = [_device newTextureWithDescriptor:textureDescriptor];

    MTLRegion region;
    region.origin.x = 0;
    region.origin.y = 0;
    region.origin.z = 0;
    region.size.width = (NSUInteger)size.width();
    region.size.height = (NSUInteger)size.height();
    region.size.depth = 1;

    NSUInteger bytesPerRow = 4 * (NSUInteger)size.width();
    [mtlTexture replaceRegion:region mipmapLevel:0 withBytes:texture->raw() bytesPerRow:bytesPerRow];

    if (!_textures) {
        _textures = [[NSMutableArray alloc] init];
    }
    [_textures addObject:mtlTexture];
    texture->_set_handle([_textures count] - 1);
}

- (id <MTLTexture>)textureUsing:(std::shared_ptr<diamane::gl::texture>)texture
{
    return [_textures objectAtIndex:texture->handle()];
}

// MARK: - Render/Draw

- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture
{
    [self drawAtPoint:point texture:texture uv:0];
}

- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index
{
    [self drawInRect:diamane::rect(point, texture->uv(uv_index).size()) texture:texture uv:uv_index];
}

- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture
{
    [self drawInRect:rect texture:texture uv:0];
}

- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index
{
    std::array<diamane::shader::metal::vertex_descriptor, 6> v;

    auto x = static_cast<float>(rect.origin().x());
    auto y = static_cast<float>(rect.origin().y());
    auto w = static_cast<float>(rect.size().width());
    auto h = static_cast<float>(rect.size().height());

    // Specify the positions of each vertex
    v[0].position = vector2( x -w, y +h );
    v[1].position = vector2( x +w, y +h );
    v[2].position = vector2( x +w, y -h );
    v[3].position = vector2( x -w, y +h );
    v[4].position = vector2( x -w, y -h );
    v[5].position = vector2( x +w, y -h );

    // Setup the UV Mapping for the verticies
    auto uv = texture->uv(uv_index);
    auto uv_x = static_cast<float>(uv.origin().x()) / static_cast<float>(w);
    auto uv_y = static_cast<float>(uv.origin().y()) / static_cast<float>(h);
    auto uv_w = static_cast<float>(uv.size().width()) / static_cast<float>(w);
    auto uv_h = static_cast<float>(uv.size().height()) / static_cast<float>(h);

    v[0].texture_coord = vector2(static_cast<float>(uv_x), static_cast<float>(uv_y));
    v[1].texture_coord = vector2(static_cast<float>(uv_x + uv_w), static_cast<float>(uv_y));
    v[2].texture_coord = vector2(static_cast<float>(uv_x + uv_w), static_cast<float>(uv_y + uv_h));
    v[3].texture_coord = vector2(static_cast<float>(uv_x), static_cast<float>(uv_y));
    v[4].texture_coord = vector2(static_cast<float>(uv_x), static_cast<float>(uv_y + uv_h));
    v[5].texture_coord = vector2(static_cast<float>(uv_x + uv_w), static_cast<float>(uv_y + uv_h));

    // Setup the color of each vertex.
    auto white = diamane::gl::color::whiteColor();
    v[0].color = color_vector(white);
    v[1].color = color_vector(white);
    v[2].color = color_vector(white);
    v[3].color = color_vector(white);
    v[4].color = color_vector(white);
    v[5].color = color_vector(white);

    // Configure the scale
    v[0].scale = v[1].scale
            = v[2].scale
            = v[3].scale
            = v[4].scale
            = v[5].scale = [self nativeScale];

    // Enqueue a render command for the texture.
    [self setPipelineStateForIndex:0];

    id <MTLRenderCommandEncoder> encoder = [self commandEncoder];
    vector_uint2 *viewport_size = [self viewportSize];

    [_commandEncoder setVertexBytes:&v[0] length:(sizeof(diamane::shader::metal::vertex_descriptor) * v.size())
                            atIndex:diamane::shader::metal::vertex_input_index::vertices];
    [_commandEncoder setVertexBytes:viewport_size length:sizeof(*viewport_size)
                            atIndex:diamane::shader::metal::vertex_input_index::viewport_size];

    if (texture != nullptr) {
        [encoder setFragmentTexture:[self textureUsing:texture]
                            atIndex:diamane::shader::metal::texture_index::base_color];
    }

    [_commandEncoder drawPrimitives:MTLPrimitiveTypeTriangleStrip
                        vertexStart:0
                        vertexCount:v.size()];

    [self restorePipelineState];
}

@end

#endif