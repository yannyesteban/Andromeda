precision mediump float;

varying vec3 fColor;

//uniform vec4 textColor;



void main() {


    gl_FragColor = vec4(fColor,1.0);
}