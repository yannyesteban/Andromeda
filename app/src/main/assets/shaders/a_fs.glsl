precision mediump float;
varying vec2 fColor;

uniform sampler2D uTexture;
void main() {
    vec4 texColor = texture2D(uTexture, fColor);



    if(texColor.a < 0.1){
        discard;
    }


    gl_FragColor = texColor;
}
