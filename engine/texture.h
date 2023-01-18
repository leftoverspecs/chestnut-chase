#pragma once

#include <GL/glew.h>

#include <optional>

namespace engine {

class Texture {
public:
    class Binding {
    public:
        ~Binding();

        void image_2d(GLint level, GLint internalformat, GLsizei width,
                      GLsizei height, GLint border, GLenum format,
                      GLenum type, const void *data) const;
        void set_parameter(GLenum pname, GLint param) const;
        void generate_mipmap() const;
        void clear(GLint level, GLenum format, GLenum type, const void *data) const;

        Binding(const Binding &) = delete;
        Binding(Binding &&) = delete;
        Binding &operator = (const Binding &) = delete;
        Binding &operator = (Binding &&) = delete;
    private:
        friend class Texture;
        Binding(GLenum texture_unit, GLenum target, const Texture &texture);

        GLenum texture_unit;
        GLenum target;
    };

    Texture();
    Texture(const unsigned char *bmp, std::size_t size);
    ~Texture();

    Binding bind(GLenum texture_unit, GLenum target) const;

    GLuint get_id() const { return id; }

    Texture(const Texture &) = delete;
    Texture &operator = (const Texture &) = delete;
private:
    GLuint id;
};

}
