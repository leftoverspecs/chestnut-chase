#version 330 core
in vec2 position;
in vec2 texture_coord;

out vec2 frag_texture_coord;

uniform float x_offset;
uniform float y_offset;

void main() {
    frag_texture_coord = texture_coord;
    gl_Position = vec4(position.x + x_offset, position.y + y_offset, 0, 1);
}
