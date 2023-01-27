#version 330 core
in vec2 frag_position;
in vec2 frag_texture_coord;

uniform sampler2D source_texture;
uniform vec3 color;

out vec4 FragColor;

void main() {
    FragColor = texture(source_texture, frag_texture_coord) + (0.5 * dot(frag_position, frag_position) * vec4(color, 1.0));
}
