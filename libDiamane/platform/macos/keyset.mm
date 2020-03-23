//
// Created by Tom Hancocks on 23/02/2020.
//

#if __APPLE__

#include "libDiamane/platform/keyset.hpp"

@import Cocoa;
@import CoreGraphics;

auto diamane::platform::key_set::capture_keys() -> void
{
    static CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventSourceStateID stateId = CGEventSourceGetSourceStateID(source);

    m_cursor_down = CGEventSourceKeyState(stateId, 0x7d);
    m_cursor_up = CGEventSourceKeyState(stateId, 0x7e);
    m_cursor_left = CGEventSourceKeyState(stateId, 0x7b);
    m_cursor_right = CGEventSourceKeyState(stateId, 0x7c);

    m_space = CGEventSourceKeyState(stateId, 0x31);
    m_esc = CGEventSourceKeyState(stateId, 0x35);
}

#endif