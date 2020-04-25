//
// Created by tomhancocks on 24/04/2020.
//

#if __linux__

#include "libDiamane/platform/application.hpp"
#include "GL/freeglut.h"
#include "GL/gl.h"

// MARK: - Main Application Run Loop

auto diamane::platform::application::run(int argc, const char **argv, std::function<void()> setupFn) -> void
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_SINGLE);
    setupFn();
    glutMainLoop();
}

// MARK: -

auto diamane::platform::application::acquire_handle() -> diamane::handle
{
    return diamane::handle();
}

auto diamane::platform::application::set_menubar(std::shared_ptr<diamane::ui::menubar> menubar) -> void
{

}

auto diamane::platform::key_set::capture_keys() -> void
{

}

#endif