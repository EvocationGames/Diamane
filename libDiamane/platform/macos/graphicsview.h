//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__ && !defined(DIAMANE_GRAPHICSVIEW_H)
#define DIAMANE_GRAPHICSVIEW_H

@import Cocoa;

#include <functional>
#include "libDiamane/graphics/texture.hpp"
#include "libDiamane/util/geometry.hpp"

// MARK: - Graphics Modes

typedef NS_ENUM(NSInteger, DiamaneMacOSGraphicsMode)
{
    DiamaneMacOSGraphicsMode_None,
    DiamaneMacOSGraphicsMode_Metal,
    DiamaneMacOSGraphicsMode_OpenGL
};

// MARK: - Internal Graphics View

@protocol DeviceDependantGraphicsViewProtocol
- (void)configure;
- (void)registerTexture:(std::shared_ptr<diamane::gl::texture>)texture;
- (void)drawAtPoint:(diamane::point)point texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index;
- (void)drawInRect:(diamane::rect)rect texture:(std::shared_ptr<diamane::gl::texture>)texture uv:(int)uv_index;
- (void)setBackgroundColor:(const diamane::gl::color)clearColor;
@end

// MARK: - Container Graphics View

@interface GraphicsView: NSView
@property (nonatomic, assign) DiamaneMacOSGraphicsMode graphicsMode;
@property (nonatomic, nullable, retain) id<DeviceDependantGraphicsViewProtocol> deviceGraphicsView;

- (bool)lock;
- (void)unlock;

- (void)onDraw:(std::function<void()>)callback;
- (void)setBackgroundColor:(const diamane::gl::color)color;
@end

#endif //DIAMANE_GRAPHICSVIEW_H
