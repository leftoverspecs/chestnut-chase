#version 330 core
in vec2 frag_position;
in vec2 frag_texture_coord;

uniform sampler2D source_texture;
uniform vec3 color;

out vec4 FragColor;

void main() {
    const float exposure = 1.0;
    const float gamma = 2.2;
    vec3 color = texture(source_texture, frag_texture_coord).rgb + (0.1 * dot(frag_position, frag_position) * color);
    vec3 result = vec3(1.0) - exp(-color * exposure);
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}
