//
// Created by Tom Hancocks on 22/02/2020.
//

#include "libDiamane/platform/application.hpp"

// MARK: - Constructors

diamane::platform::application::application()
    : m_handle(acquire_handle())
{

}

auto diamane::platform::application::shared() -> std::shared_ptr<diamane::platform::application>
{
    static diamane::platform::application app;
    return std::make_shared<diamane::platform::application>(app);
}

// MARK:
