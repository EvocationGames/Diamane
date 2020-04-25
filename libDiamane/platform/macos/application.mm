//
// Created by Tom Hancocks on 22/02/2020.
//

#if __APPLE__

#include "libDiamane/platform/application.hpp"

@import Cocoa;

// MARK: - Setup Cocoa Application

@interface DiamaneApplication: NSObject <NSApplicationDelegate>
- (void)run:(std::function<void()>)setupFn;
- (void)setMenuBar:(NSMenu *)menuBar;
@end

@implementation DiamaneApplication {
@private
    NSApplication *_app;
}

// MARK: - Initialiser

- (instancetype)init
{
    if (self = [super init]) {
        _app = [NSApplication sharedApplication];
        [_app setActivationPolicy:NSApplicationActivationPolicyRegular];
        [_app setDelegate:self];
    }
    return self;
}

// MARK: - MenuBar

- (void)setMenuBar:(NSMenu *)menuBar
{
    [_app setMainMenu:menuBar];
}

// MARK: - Runner

- (void)run:(std::function<void()>)setupFn
{
    @autoreleasepool {
        setupFn();
        [_app activateIgnoringOtherApps:true];
        [_app run];
    }
}

@end

auto diamane::platform::application::run(int argc, const char **argv, std::function<void()> setupFn) -> void
{
    if (auto app = m_handle.get<DiamaneApplication *>()) {
        [app run:setupFn];
    }
}

// MARK: - Menu Bar

auto diamane::platform::application::set_menubar(std::shared_ptr<diamane::ui::menubar> menubar) -> void
{
    if (auto app = m_handle.get<DiamaneApplication *>()) {
        if (auto menuBar = menubar->handle().get<NSMenu *>()) {
            [app setMenuBar:menuBar];
        }
    }
}

// MARK: - Application Handle

auto diamane::platform::application::acquire_handle() -> diamane::handle
{
    DiamaneApplication *app = [[DiamaneApplication alloc] init];
    return make_handle(app);
}

#endif