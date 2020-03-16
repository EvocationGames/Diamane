//
// Created by Tom Hancocks on 28/02/2020.
//

#if !defined(DIAMANE_BUTTON_HPP)
#define DIAMANE_BUTTON_HPP

#include <memory>
#include <string>
#include "libDiamane/graphics/texture.hpp"

namespace diamane { namespace ui {

    class button: public std::enable_shared_from_this<button>
    {
    private:
        std::string m_title { "Button" };
        rect m_frame { 0, 0, 60, 20 };
        std::shared_ptr<gl::texture> m_left_cap;
        std::shared_ptr<gl::texture> m_fill;
        std::shared_ptr<gl::texture> m_right_cap;
    public:

        button(std::string title, rect frame);

        static auto create(std::string title, rect frame) -> std::shared_ptr<button>;

        auto draw() -> void;

    };

}};

#endif //DIAMANE_BUTTON_HPP
