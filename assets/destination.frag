#version 330 core
in vec2 frag_texture_coord;

uniform sampler2D source_texture;

out vec4 FragColor;

void main() {
    FragColor = texture(source_texture, frag_texture_coord);
}
