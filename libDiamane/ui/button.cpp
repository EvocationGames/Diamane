//
// Created by Tom Hancocks on 28/02/2020.
//

#include "libDiamane/ui/button.hpp"
#include "libDiamane/graphics/graphics.hpp"

// MARK: - Constructors

diamane::ui::button::button(std::string title, rect frame)
    : m_title(title), m_frame(frame)
{
    // Allocate the cap textures
    m_left_cap = diamane::gl::texture::blank(size(5, 20));
    m_right_cap = diamane::gl::texture::blank(size(5, 20));
    m_fill = diamane::gl::texture::blank(size(1, 20));

    // Paint the textures
    m_left_cap->paint([&] (std::shared_ptr<gl::graphics> g) {
        g->fill_rect(rect(0, 0, 5, 20), gl::color(0.7));
        g->fill_rect(rect(1, 1, 4, 18), gl::color(0.9));
    });

    m_fill->paint([&] (std::shared_ptr<gl::graphics> g) {
        g->fill_rect(rect(0, 0, 1, 20), gl::color(0.7));
        g->fill_rect(rect(0, 1, 1, 18), gl::color(0.9));
    });

    m_right_cap->paint([&] (std::shared_ptr<gl::graphics> g) {
        g->fill_rect(rect(0, 0, 5, 20), gl::color(0.7));
        g->fill_rect(rect(0, 1, 4, 18), gl::color(0.9));
    });
}

auto diamane::ui::button::create(std::string title, rect frame) -> std::shared_ptr<diamane::ui::button>
{
    return std::make_shared<diamane::ui::button>(title, frame);
}

auto diamane::ui::button::draw() -> void
{
    m_left_cap->draw(point::zero());


    // Calculate where each of the textures is being draw
//    m_left_cap->draw(point(m_frame.min_x() - m_frame.width(), m_frame.min_y()));
//    m_fill->draw(rect(
//            m_frame.min_x() + m_left_cap->size().width(),
//            m_frame.min_y(),
//            m_frame.width() - m_left_cap->size().width() - m_right_cap->size().width(),
//            m_fill->size().height()));
//    m_right_cap->draw(point(m_frame.max_x() - m_right_cap->size().width(), m_frame.min_y()));
}
