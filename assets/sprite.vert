#version 330 core
in vec2 position;
in vec4 color;
in vec2 texture_coord;

out vec4 frag_color;
out vec2 frag_texture_coord;

uniform float width;
uniform float height;

void main() {
    frag_color = color;
    frag_texture_coord = texture_coord;
    gl_Position = vec4(2 * position.x / width - 1, 2 * position.y / height - 1, 0, 1);
}
