#version 330 core
in vec2 frag_texture_coord;

uniform sampler2D sprite_texture;

out vec4 FragColor;

void main() {
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = vec4(texture(sprite_texture, frag_texture_coord).rgb, 1.0);
    //FragColor = vec4(texture(sprite_texture, vec2(1.0, 0.0)).rgb, 1.0);
}
