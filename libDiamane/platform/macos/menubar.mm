//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__

#include "libDiamane/ui/menubar.hpp"

@import Cocoa;

// MARK: - MenuBar Handle

auto diamane::ui::menubar::acquire_handle() -> diamane::handle
{
    NSMenu *mainMenu = [[NSMenu alloc] init];
    NSMenu *appMenu = [[NSMenu alloc] init];

    NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
    appMenuItem.submenu = appMenu;
    [mainMenu addItem:appMenuItem];

    NSString *quitMenuItemTitle = [NSString stringWithFormat:@"Quit %@", [[NSProcessInfo processInfo] processName]];
    NSMenuItem *quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitMenuItemTitle
                                                          action:@selector(terminate:)
                                                   keyEquivalent:@"q"];
    [quitMenuItem setAction:@selector(terminate:)];
    [appMenu addItem:quitMenuItem];

    return make_handle(mainMenu);
}

#endif
