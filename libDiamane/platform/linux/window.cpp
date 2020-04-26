//
// Created by tomhancocks on 24/04/2020.
//

#if __linux__

#include "libDiamane/ui/window.hpp"
#include "GL/gl.h"
#include "GL/freeglut.h"

// MARK: - Active Window

static std::shared_ptr<diamane::ui::window> m_window = nullptr;

static auto window_draw() -> void
{
    m_window->draw();
}

static auto window_reshape(GLint width, GLint height) -> void
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, width, 0.0, height);
}

// MARK: -

auto diamane::ui::window::acquire_handle() -> diamane::handle
{
    uintptr_t ptr = static_cast<uintptr_t>(glutCreateWindow(m_title.c_str()));
    glutHideWindow();
    return make_handle(reinterpret_cast<const void *>(ptr));
}

auto diamane::ui::window::set_background_color(const diamane::gl::color color) -> void
{
    m_background_color = color;
}

auto diamane::ui::window::set_title(const std::string title) -> void
{
    m_title = title;

    auto ptr = reinterpret_cast<uintptr_t>(m_handle.get<const int*>());
    glutSetWindow(ptr);
    glutSetWindowTitle(title.c_str());
}

auto diamane::ui::window::set_size(diamane::size size) -> void
{
    if (m_handle.get<const void *>() != nullptr) {
        // Destroy the existing window.
        glutDestroyWindow(reinterpret_cast<uintptr_t>(m_handle.get<const int*>()));
    }

    m_size = size;
    glutInitWindowSize(size.width(), size.height());
    m_handle = acquire_handle();
}

auto diamane::ui::window::center() -> void
{

}

auto diamane::ui::window::show() -> void
{
    auto ptr = reinterpret_cast<uintptr_t>(m_handle.get<const int*>());
    glutSetWindow(ptr);
    glutShowWindow();

    // Make the active window this one.
    m_window = shared_from_this();
}

auto diamane::ui::window::on_draw(std::function<void ()> fn) -> void
{
    m_draw = fn;

    auto ptr = reinterpret_cast<uintptr_t>(m_handle.get<const int*>());
    glutSetWindow(ptr);
    glutDisplayFunc(window_draw);
    glutReshapeFunc(window_reshape);
}

// MARK: -

auto diamane::ui::window::draw() -> void
{
    clear();
    m_draw();
    glFlush();
}

auto diamane::ui::window::clear() -> void
{
    glClearColor(m_background_color.red(), m_background_color.green(), m_background_color.blue(), m_background_color.alpha());
    glClear(GL_COLOR_BUFFER_BIT);
}

#endif