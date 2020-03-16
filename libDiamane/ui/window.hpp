//
// Created by Tom Hancocks on 22/02/2020.
//

#if !defined(DIAMANE_WINDOW_HPP)
#define DIAMANE_WINDOW_HPP

#include <string>
#include <memory>
#include "libDiamane/util/hints.hpp"
#include "libDiamane/util/handle.hpp"
#include "libDiamane/util/geometry.hpp"
#include "libDiamane/graphics/color.hpp"

namespace diamane { namespace ui {

    class window: public std::enable_shared_from_this<window>
    {
    private:
        std::string m_title { "Untitled Window" };
        handle m_handle;
        diamane::gl::color m_background_color { 0, 0, 0 };

        __platform_specific static auto _acquire_handle() -> handle;

    public:

        window(const std::string title, const diamane::size size);

        static auto create(const std::string title, const diamane::size size = diamane::size(300, 300)) -> std::shared_ptr<window>;

        __platform_specific auto show() -> void;
        __platform_specific auto close() -> void;
        __platform_specific auto center() -> void;
        __platform_specific auto set_title(const std::string title) -> void;
        __platform_specific auto set_size(diamane::size size) -> void;
        __platform_specific auto set_background_color(const diamane::gl::color color) -> void;

        handle acquire_handle();

        __platform_specific auto on_draw(std::function<void()> fn) -> void;
    };

}};

#endif //DIAMANE_WINDOW_HPP
