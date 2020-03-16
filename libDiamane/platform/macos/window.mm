//
// Created by Tom Hancocks on 22/02/2020.
//

#if __APPLE__

#include "libDiamane/ui/window.hpp"
#include "libDiamane/platform/macos/graphicsview.h"

@import Cocoa;

// MARK: - Cocoa Window Support

@interface Window: NSWindow
@property (nonatomic, nullable, retain) GraphicsView *graphicsView;
@end

@implementation Window

+ (nullable instancetype)window
{
    Window *wnd = [[Window alloc] initWithContentRect:NSMakeRect(0, 0, 100, 100)
                                            styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable
                                              backing:NSBackingStoreBuffered
                                                defer:YES];

    // Setup a graphics view for the window. The type of graphics can be configured later.
    [wnd setGraphicsView:[[GraphicsView alloc] initWithFrame:[[wnd contentView] frame]]];
    [wnd setContentView:[wnd graphicsView]];
    [[wnd graphicsView] setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [[wnd graphicsView] setWantsLayer:YES];
    [[wnd graphicsView] setGraphicsMode:DiamaneMacOSGraphicsMode_Metal];

    // Return the window to the caller.
    return wnd;
}

@end


auto diamane::ui::window::acquire_handle() -> diamane::handle
{
    return diamane::make_handle([Window window]);
}

// MARK: - Window Functions

auto diamane::ui::window::show() -> void
{
    if (auto wnd = m_handle.get<Window *>()) {
        [wnd makeKeyAndOrderFront:nil];
    }
}

auto diamane::ui::window::close() -> void
{

}

auto diamane::ui::window::center() -> void
{
    if (auto wnd = m_handle.get<Window *>()) {
        [wnd center];
    }
}

auto diamane::ui::window::set_title(const std::string title) -> void
{
    if (auto wnd = m_handle.get<Window *>()) {
        [wnd setTitle:[NSString stringWithUTF8String:title.c_str()]];
    }
}

auto diamane::ui::window::set_size(diamane::size size) -> void
{
    if (auto wnd = m_handle.get<Window *>()) {
        auto width = size.width();
        auto height = size.height();
        [wnd setContentSize:NSMakeSize(width, height)];
    }
}

auto diamane::ui::window::set_background_color(const diamane::gl::color color) -> void
{
    m_background_color = color;
    if (auto wnd = m_handle.get<Window *>()) {
        [[wnd graphicsView] setBackgroundColor:color];
    }
}

// MARK: - Callbacks

auto diamane::ui::window::on_draw(std::function<void()> fn) -> void
{
    if (auto wnd = m_handle.get<Window *>()) {
        auto graphicsView = [wnd graphicsView];
        [graphicsView onDraw:fn];
    }
}

#endif