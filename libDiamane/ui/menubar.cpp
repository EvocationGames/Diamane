//
// Created by Tom Hancocks on 23/02/2020.
//

#include "libDiamane/ui/menubar.hpp"

// MARK: - Constructors

diamane::ui::menubar::menubar()
    : m_handle(acquire_handle())
{

}

auto diamane::ui::menubar::create() -> std::shared_ptr<diamane::ui::menubar>
{
    return std::make_shared<diamane::ui::menubar>();
}

// MARK: - Accessors

auto diamane::ui::menubar::handle() -> diamane::handle
{
    return m_handle;
}