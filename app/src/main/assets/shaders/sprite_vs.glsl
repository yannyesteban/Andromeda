attribute vec3 vPosition;
attribute vec2 vTexture;
uniform mat4 MVP;
varying vec2 fTexture;
void main() {
    gl_Position = MVP * vec4(vPosition, 1.0);
    fTexture = vTexture;
}
