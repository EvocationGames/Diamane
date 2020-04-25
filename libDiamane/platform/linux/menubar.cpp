//
// Created by tomhancocks on 24/04/2020.
//

#if __linux__

#include "libDiamane/ui/menubar.hpp"
#include "libDiamane/util/handle.hpp"

// MARK: - Handle

auto diamane::ui::menubar::acquire_handle() -> diamane::handle
{
    return {};
}

#endif