//
// Created by Tom Hancocks on 22/02/2020.
//

#if !defined(DIAMANE_GEOMETRY_HPP)
#define DIAMANE_GEOMETRY_HPP

#include <cstdint>

namespace diamane
{
    /**
     * Represents a point in 2Dimensional space as represented by (x y) coordinates.
     */
    struct point
    {
    private:
        double m_x;
        double m_y;
    public:
        point(const double x, const double y) : m_x(x), m_y(y) {};

        static auto zero() -> point { return point(0, 0); }

        auto x() const -> double { return m_x; };
        auto y() const -> double { return m_y; };
    };

    /**
     * Represents a size/area in 2Dimensional space as represented by (width height) values.
     */
    struct size
    {
    private:
        double m_width;
        double m_height;
    public:
        size(const double width, const double height) : m_width(width), m_height(height) {};

        static auto zero() -> size { return size(0, 0); }

        auto width() const -> double { return m_width; };
        auto height() const -> double { return m_height; };
    };

    /**
     * Represents a rectangle.
     */
     struct rect
     {
     private:
         point m_origin;
         size m_size;
     public:
         rect(point origin, size sz) : m_origin(origin), m_size(sz) {};
         rect(const double x, const double y, const double width, const double height) : m_origin(x, y), m_size(width, height) {};

         static auto zero() -> rect { return rect(point::zero(), size::zero()); };

         auto origin() const -> point { return m_origin; };
         auto size() const -> size { return m_size; };

         auto min_x() const -> double { return m_origin.x(); };
         auto min_y() const -> double { return m_origin.y(); };
         auto max_x() const -> double { return m_origin.x() + m_size.width(); };
         auto max_y() const -> double { return m_origin.y() + m_size.height(); };

         auto width() const -> double { return m_size.width(); };
         auto height() const -> double { return m_size.height(); };

         auto contains(point p) const -> bool { return (p.x() >= min_x() && p.x() < max_x()) && (p.y() >= min_y() && p.y() < max_y()); };
         auto contains(rect r) const -> bool { return (r.min_x() >= min_x()) && (r.min_y() >= min_y()) && (r.max_x() <= max_x()) && (r.max_y() <= max_y()); };
     };

};

#endif //DIAMANE_GEOMETRY_HPP
