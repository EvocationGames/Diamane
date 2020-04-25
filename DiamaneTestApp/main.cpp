//
// Created by Tom Hancocks on 22/02/2020.
//

#include <iostream>
#include "libDiamane/graphics/texture.hpp"
#include "libDiamane/platform/application.hpp"
#include "libDiamane/ui/window.hpp"
#include "libDiamane/ui/button.hpp"

auto main(int argc, const char *argv[]) -> int
{
    auto app = diamane::platform::application::shared();
    auto btn = diamane::ui::button::create("Button", diamane::rect(0, 0, 100, 20));
    auto tex = diamane::gl::texture::blank(diamane::size(100, 100));

    app->run(argc, argv, [&app, &btn, &tex] {
        // Setup a new MenuBar
        app->set_menubar(diamane::ui::menubar::create());

        // Create a window.
        auto window = diamane::ui::window::create("Test Window");
        window->set_background_color(diamane::gl::color::redColor());
        window->show();

        // Draw the texture into the window upon each draw request.
        window->on_draw([&tex] {
            tex->draw(diamane::point(0, 0));
        });

    });
    return 0;
}
