//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__ && !defined(DIAMANE_METALGRAPHICS_H)
#define DIAMANE_METALGRAPHICS_H

#include <memory>
#include "libDiamane/graphics/texture.hpp"

@import Cocoa;
@import Metal;
@import MetalKit;
@import simd;

@class MetalGraphicsView;

@interface MetalGraphics: NSObject <MTKViewDelegate>

@property (nonatomic, readonly, retain) id <MTLRenderCommandEncoder> commandEncoder;
@property (nonatomic, readonly) float nativeScale;
@property (nonatomic, readonly, assign) vector_uint2 *viewportSize;

+ (instancetype)graphicsForView:(MetalGraphicsView *)graphicsView usingDevice:(id<MTLDevice>)device;

- (void)restorePipelineState;
- (void)setPipelineStateForIndex:(int)index;

- (void)registerTexture:(std::shared_ptr<diamane::gl::texture>)texture;
- (id <MTLTexture>)textureUsing:(std::shared_ptr<diamane::gl::texture>)texture;

- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index;
- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index;

@end

#endif //DIAMANE_METALGRAPHICS_H
