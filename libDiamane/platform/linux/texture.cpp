//
// Created by tomhancocks on 24/04/2020.
//

#if __linux__

#include "libDiamane/graphics/texture.hpp"
#include "GL/freeglut.h"
#include "GL/gl.h"

auto diamane::gl::texture::draw(diamane::rect rect, int uv_index) -> void
{
    if (!is_registered()) {
        register_texture();
    }

    auto l = static_cast<GLfloat>(rect.min_x());
    auto t = static_cast<GLfloat>(rect.min_y());
    auto r = static_cast<GLfloat>(rect.max_x());
    auto b = static_cast<GLfloat>(rect.max_x());

    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(l, t);
    glTexCoord2i(0, 1); glVertex2i(l, b);
    glTexCoord2i(1, 1); glVertex2i(r, b);
    glTexCoord2i(1, 0); glVertex2i(r, t);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

}

auto diamane::gl::texture::draw(diamane::point point, int uv_index) -> void
{
    diamane::rect r(point, m_size);
    draw(r, uv_index);
}

// MARK: - Texture Registering

auto diamane::gl::texture::register_texture() -> void
{
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            m_size.width(), m_size.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, m_data.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    m_handle = tex;
}

#endif