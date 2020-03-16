//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__

@import Cocoa;
#import <libDiamane/graphics/texture.hpp>
#include "libDiamane/platform/macos/graphicsview.h"
#include "libDiamane/platform/macos/metal/metalgraphicsview.h"

// MARK: - GraphicsView

static GraphicsView *__activeGraphicsView = nil;
static int __activeLockCount = 0;

@implementation GraphicsView {
@private
    std::function<void()> _onDrawCallback;
}

// MARK: - Callbacks

- (void)onDraw:(std::function<void()>)callback
{
    _onDrawCallback = callback;
}

// MARK: - Mode

- (void)setGraphicsMode:(DiamaneMacOSGraphicsMode)graphicsMode
{
    if (_graphicsMode == graphicsMode) {
        return;
    }

    // TODO: Disable the existing graphics mode!
    [(NSView *)_deviceGraphicsView removeFromSuperview];

    _graphicsMode = graphicsMode;
    switch (graphicsMode) {
        case DiamaneMacOSGraphicsMode_Metal:
            _deviceGraphicsView = [[MetalGraphicsView alloc] initWithFrame:[self bounds]];
            [_deviceGraphicsView configure];
            break;
        default:
            break;
    }

    if (_deviceGraphicsView) {
        [_deviceGraphicsView setClearColor:diamane::gl::color::blackColor()];
        [(NSView *)_deviceGraphicsView setAutoresizingMask:NSViewWidthSizable|NSViewHeightSizable];
        [self addSubview:(NSView *)_deviceGraphicsView];
    }

    // TODO: Enable the new graphics mode.
}

// MARK: - Locking

- (bool)lock
{
    if (__activeGraphicsView && __activeGraphicsView != self) {
        return false;
    }
    __activeLockCount++;
    __activeGraphicsView = self;
    return true;
}

- (void)unlock
{
    if (--__activeLockCount <= 0) {
        __activeGraphicsView = nil;
    }
}

// MARK: - Frame Lifecycle Methods

- (void)frameStart
{

}

- (void)frameDraw
{
    if (_onDrawCallback) {
        _onDrawCallback();
    }
}

- (void)frameEnd
{

}

@end

// MARK: - Color

@interface GraphicsView (BackgroundColor)
- (void)setBackgroundColor:(const diamane::gl::color)color;
@end

@implementation GraphicsView (BackgroundColor)

- (void)setBackgroundColor:(const diamane::gl::color)color
{
    [_deviceGraphicsView setBackgroundColor:color];
}

@end

// MARK: - Texture Drawing

@interface GraphicsView (Textures)
- (void)registerTexture:(std::shared_ptr<diamane::gl::texture>)texture;
- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index;
- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index;
@end

auto diamane::gl::texture::draw(diamane::point point, int uv_index) -> void
{
    if (!is_registered()) {
        register_texture();
    }
    [__activeGraphicsView drawAtPoint:point texture:shared_from_this() uv:uv_index];
}

auto diamane::gl::texture::draw(diamane::rect rect, int uv_index) -> void
{
    if (!is_registered()) {
        register_texture();
    }
    [__activeGraphicsView drawInRect:rect texture:shared_from_this() uv:uv_index];
}

auto diamane::gl::texture::register_texture() -> void
{
    [__activeGraphicsView registerTexture:shared_from_this()];
}

@implementation GraphicsView (Textures)

- (void)registerTexture:(std::shared_ptr<diamane::gl::texture>)texture
{
    [_deviceGraphicsView registerTexture:texture];
}

- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index
{
    [_deviceGraphicsView drawAtPoint:point texture:texture uv:uv_index];
}

- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index
{
    [_deviceGraphicsView drawInRect:rect texture:texture uv:uv_index];
}

@end

#endif