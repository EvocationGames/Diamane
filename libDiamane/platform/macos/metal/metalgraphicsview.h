//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__ && !defined(DIAMANE_METALGRAPHICSVIEW_HPP)
#define DIAMANE_METALGRAPHICSVIEW_HPP

#include "libDiamane/platform/macos/graphicsview.h"

@import MetalKit;

@class MetalGraphics;

@interface MetalGraphicsView: MTKView <DeviceDependantGraphicsViewProtocol>

@property (nonatomic, readonly) MetalGraphics *metal;

- (void)setBackgroundColor:(const diamane::gl::color)clearColor;

- (void)configure;

- (void)frameStart;
- (void)frameDraw;
- (void)frameEnd;

@end

#endif //DIAMANE_METALGRAPHICSVIEW_HPP
