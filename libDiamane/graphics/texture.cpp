//
// Created by Tom Hancocks on 24/02/2020.
//

#include "libDiamane/graphics/texture.hpp"

// MARK: - Constructors

diamane::gl::texture::texture(std::vector<uint32_t> raw_data, diamane::size size)
    : m_size(size), m_data(raw_data)
{
    setup_single_uv();
}

auto diamane::gl::texture::blank(diamane::size size) -> std::shared_ptr<diamane::gl::texture>
{
    return std::make_shared<diamane::gl::texture>(std::vector<uint32_t>(size.width() * size.height(), 0xFFFFFFFF), size);
}

auto diamane::gl::texture::from_raw(std::vector<uint32_t> raw_data, diamane::size size) -> std::shared_ptr<texture>
{
    return std::make_shared<diamane::gl::texture>(raw_data, size);
}

// MARK: - Texture Painting

auto diamane::gl::texture::paint(std::function<void(std::shared_ptr<diamane::gl::graphics>)> fn) -> void
{
    auto graphics = std::make_shared<diamane::gl::graphics>(&m_data[0], m_size);
    fn(graphics);
}

// MARK: - Accessors

auto diamane::gl::texture::size() const -> diamane::size
{
    return m_size;
}

auto diamane::gl::texture::raw() const -> const void *
{
    return reinterpret_cast<const void *>(&m_data[0]);
}

auto diamane::gl::texture::handle() -> int64_t
{
    return m_handle;
}

auto diamane::gl::texture::_set_handle(int64_t handle) -> void
{
    m_handle = handle;
}

auto diamane::gl::texture::is_registered() const -> bool
{
    return m_handle >= 0;
}

// MARK: - UV

auto diamane::gl::texture::uv(int index) const -> diamane::rect
{
    return m_uv_map[index];
}

auto diamane::gl::texture::setup_single_uv() -> void
{
    m_uv_map.clear();
    m_uv_map.emplace_back(0, 0, m_size.width(), m_size.height());
}

auto diamane::gl::texture::clear_uvs() -> void
{
    m_uv_map.clear();
}

auto diamane::gl::texture::add_uv(const diamane::rect& r) -> void
{
    m_uv_map.emplace_back(r);
}