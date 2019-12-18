
attribute vec3 vPosition;
attribute vec2 vColor;

varying vec2 fColor;
void main() {
    gl_Position = vec4(vPosition, 1.0);
    fColor = vColor;
}
