//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__

#include <memory>
#include "libDiamane/platform/macos/metal/metalgraphicsview.h"
#include "libDiamane/platform/macos/metal/metalgraphics.h"
#include "libDiamane/graphics/texture.hpp"
#include "libDiamane/util/geometry.hpp"

@interface GraphicsView ()
- (void)frameStart;
- (void)frameDraw;
- (void)frameEnd;
@end

@implementation MetalGraphicsView

- (void)setBackgroundColor:(const diamane::gl::color)clearColor
{
    [self setClearColor:MTLClearColorMake(clearColor.red(), clearColor.green(), clearColor.blue(), clearColor.alpha())];
}

- (void)configure
{
    _metal = [MetalGraphics graphicsForView:self usingDevice:MTLCreateSystemDefaultDevice()];
    [self setClearColor:MTLClearColorMake(0, 0, 0, 1)];
}

- (void)frameStart
{
    [(GraphicsView *)[self superview] frameStart];
}

- (void)frameDraw
{
    if ([(GraphicsView *)[self superview] lock]) {
        [(GraphicsView *) [self superview] frameDraw];
        [(GraphicsView *)[self superview] unlock];
    }
}

- (void)frameEnd
{
    [(GraphicsView *)[self superview] frameEnd];
}

// MARK: - Forwarding Methods

- (void)registerTexture:(std::shared_ptr<diamane::gl::texture>)texture
{
    [_metal registerTexture:texture];
}

- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index
{
    [_metal drawAtPoint:point texture:texture uv:uv_index];
}

- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index
{
    [_metal drawInRect:rect texture:texture uv:uv_index];
}

@end

#endif