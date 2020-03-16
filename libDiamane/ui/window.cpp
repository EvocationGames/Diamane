//
// Created by Tom Hancocks on 22/02/2020.
//

#include "libDiamane/ui/window.hpp"

// MARK: - Constructors

diamane::ui::window::window(const std::string title, const diamane::size size)
    : m_title(title), m_handle(acquire_handle())
{
    set_title(title);
    set_size(size);
}

auto diamane::ui::window::create(const std::string title, const diamane::size size) -> std::shared_ptr<diamane::ui::window>
{
    return std::make_shared<diamane::ui::window>(title, size);
}