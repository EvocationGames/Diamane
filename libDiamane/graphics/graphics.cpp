//
// Created by Tom Hancocks on 22/02/2020.
//

#include "libDiamane/graphics/graphics.hpp"
#include <iostream>

// MARK: - Constructors

diamane::gl::graphics::graphics(const void *pixbuf, diamane::size size)
    : m_pixel_buffer(pixbuf), m_size(size)
{

}

auto diamane::gl::graphics::create(const void *pixbuf, diamane::size size) -> std::shared_ptr<diamane::gl::graphics>
{
    return std::make_shared<diamane::gl::graphics>(pixbuf, size);
}

// MARK: - Drawing Operations

auto diamane::gl::graphics::fill_rect(diamane::rect rect, diamane::gl::color color) -> void
{
    auto buf = (uint32_t *)m_pixel_buffer;
    auto stride = m_size.width();
    auto color_value = color.rgb_value();

    auto min_y = rect.min_y() >= 0 ? rect.min_y() : 0;
    auto min_x = rect.min_x() >= 0 ? rect.min_x() : 0;
    auto max_y = rect.max_y() <= m_size.height() ? rect.max_y() : m_size.height();
    auto max_x = rect.max_x() <= m_size.width() ? rect.max_x() : m_size.width();

    for (auto y = min_y; y < max_y; ++y) {
        auto ptr = buf + (y * stride) + min_x;
        for (auto x = min_x; x < max_x; ++x) {
            *ptr++ = color_value;
        }
    }
}

auto diamane::gl::graphics::draw_line(diamane::point p0, diamane::point p1, diamane::gl::color color) -> void
{
    auto buf = (uint32_t *)m_pixel_buffer;
    auto width = m_size.width();
    auto color_value = color.rgb_value();

    auto x0 = p0.x();
    auto y0 = p0.y();
    auto x1 = p1.x();
    auto y1 = p1.y();

    auto delta_x = abs(x1 - x0);
    auto delta_y = abs(y1 - y0);
    auto sx = (x0 < x1) ? 1 : -1;
    auto sy = (y0 < y1) ? 1 : -1;
    auto err = delta_x - delta_y;

    for (;;) {
        if (x0 >= 0 && y0 >= 0 && x0 < m_size.width() && y0 < m_size.height()) {
            buf[y0 * width + x0] = color_value;
        }
        if (x0 == x1 && y0 == y1) {
            break;
        }
        auto e2 = 2 * err;
        if (e2 > -delta_y) {
            err -= delta_y;
            x0 += sx;
        }
        if (e2 < delta_x) {
            err += delta_x;
            y0 += sy;
        }
    }
}