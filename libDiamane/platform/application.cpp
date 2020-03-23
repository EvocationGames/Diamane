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

// MARK: - Accessors

auto diamane::platform::application::current_key_set() -> diamane::platform::key_set
{
	m_current_keys.capture_keys();
	return m_current_keys;
}
