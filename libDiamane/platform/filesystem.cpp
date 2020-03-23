//
// Created by Tom Hancocks on 23/03/2020.
//

#include "libDiamane/platform/filesystem.hpp"

// MARK: - Constructor / Singleton

diamane::platform::filesystem::filesystem()
{

}

auto diamane::platform::filesystem::shared() -> diamane::platform::filesystem&
{
    static diamane::platform::filesystem fs;
    return fs;
}

// MARK: - Path

diamane::platform::filesystem::path::path(const std::string filepath)
    : m_components(get_components_of_path(filepath))
{

}

diamane::platform::filesystem::path::path(const path &base, const std::string component)
    : m_components(base.m_components)
{
    m_components.emplace_back(component);
}

auto diamane::platform::filesystem::path::to_str() const -> std::string
{
    return diamane::platform::filesystem::path::construct_path_string(m_components);
}

auto diamane::platform::filesystem::path::append_component(const std::string component) -> void
{
    m_components.emplace_back(component);
}

auto diamane::platform::filesystem::path::remove_last_component() -> void
{
    m_components.pop_back();
}