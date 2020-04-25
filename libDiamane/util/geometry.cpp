//
// Created by tomhancocks on 24/04/2020.
//

#include "libDiamane/util/geometry.hpp"

// MARK: - Point

diamane::point::point(double x, double y)
        : m_x(x), m_y(y)
{

}

auto diamane::point::zero() -> diamane::point
{
    return diamane::point(0, 0);
}

auto diamane::point::x() const -> double
{
    return m_x;
}

auto diamane::point::y() const -> double
{
    return m_y;
}


// MARK: - Size

diamane::size::size(double width, double height)
        : m_width(width), m_height(height)
{

}

auto diamane::size::zero() -> diamane::size
{
    return diamane::size(0, 0);
}

auto diamane::size::width() const -> double
{
    return m_width;
}

auto diamane::size::height() const -> double
{
    return m_height;
}

// MARK: - Rect

diamane::rect::rect(point origin, diamane::size sz)
    : m_origin(origin), m_size(sz)
{
}

diamane::rect::rect(double x, double y, double width, double height)
    : m_origin(x, y), m_size(width, height)
{
}

auto diamane::rect::zero() -> rect
{
    return rect(diamane::point::zero(), diamane::size::zero());
}

auto diamane::rect::origin() const -> diamane::point
{
    return m_origin;
}

auto diamane::rect::size() const -> diamane::size
{
    return m_size;
}

auto diamane::rect::min_x() const -> double
{
    return m_origin.x();
}

auto diamane::rect::min_y() const -> double
{
    return m_origin.y();
}

auto diamane::rect::max_x() const -> double
{
    return m_origin.x() + m_size.width();
}

auto diamane::rect::max_y() const -> double
{
    return m_origin.y() + m_size.height();
}

auto diamane::rect::width() const -> double
{
    return m_size.width();
}

auto diamane::rect::height() const -> double
{
    return m_size.height();
}

auto diamane::rect::contains(diamane::point p) const -> bool
{
    return (p.x() >= min_x() && p.x() < max_x()) && (p.y() >= min_y() && p.y() < max_y());
}

auto diamane::rect::contains(diamane::rect r) const -> bool
{
    return (r.min_x() >= min_x()) && (r.min_y() >= min_y()) && (r.max_x() <= max_x()) && (r.max_y() <= max_y());
}
