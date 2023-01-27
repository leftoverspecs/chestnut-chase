#version 330 core
in vec2 position;
in vec2 texture_coord;

out vec2 frag_position;
out vec2 frag_texture_coord;

uniform mat4x4 projection;

void main() {
    frag_position = position;
    frag_texture_coord = texture_coord;
    gl_Position = projection * vec4(position.xy, 0, 1);
}
