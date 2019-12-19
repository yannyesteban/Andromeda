
attribute vec3 vPosition;
attribute vec2 vColor;

varying vec2 fColor;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vPosition, 1.0);
    fColor = vColor;
}
