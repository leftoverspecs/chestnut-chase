#version 330 core
in vec2 position;

uniform float width;
uniform float height;

void main() {
    gl_Position = vec4(2 * position.x / width - 1, 2 * position.y / height - 1, 0, 1);
}
