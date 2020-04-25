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
        point(double x, double y);

        static auto zero() -> diamane::point;

        auto x() const -> double;
        auto y() const -> double;
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
        size(double width, double height);

        static auto zero() -> diamane::size;

        auto width() const -> double;
        auto height() const -> double;
    };

    /**
     * Represents a rectangle.
     */
     struct rect
     {
     private:
         diamane::point m_origin;
         diamane::size m_size;
     public:
         rect(diamane::point origin, diamane::size sz);
         rect(double x, double y, double width, double height);

         static auto zero() -> diamane::rect;

         auto origin() const -> diamane::point;
         auto size() const -> diamane::size;

         auto min_x() const -> double;
         auto min_y() const -> double;
         auto max_x() const -> double;
         auto max_y() const -> double;

         auto width() const -> double;
         auto height() const -> double;

         auto contains(diamane::point p) const -> bool;
         auto contains(diamane::rect r) const -> bool;
     };

};

#endif //DIAMANE_GEOMETRY_HPP
