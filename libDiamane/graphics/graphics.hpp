//
// Created by Tom Hancocks on 22/02/2020.
//

#if !defined(DIAMANE_GRAPHICS_HPP)
#define DIAMANE_GRAPHICS_HPP

#include <memory>
#include "libDiamane/util/geometry.hpp"
#include "libDiamane/graphics/color.hpp"

namespace diamane { namespace gl {

    /**
     * The `diamane::gl::graphics` class is responsible for managing a graphics context, and dispatching
     * rendering and drawing commands.
     */
    class graphics: public std::enable_shared_from_this<graphics>
    {
    private:
        diamane::size m_size;
        const void *m_pixel_buffer;

    public:
        graphics(const void *pixbuf, diamane::size size);
        static auto create(const void *pixbuf, diamane::size size) -> std::shared_ptr<graphics>;

        auto fill_rect(diamane::rect rect, diamane::gl::color color) -> void;
        auto draw_line(diamane::point p0, diamane::point p2, diamane::gl::color color) -> void;

    };

}};

#endif //DIAMANE_GRAPHICS_HPP
