precision mediump float;
varying vec2 fTexture;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture2D(uTexture, fTexture);
    //texColor = vec4(1.0,0.3,0.3,1.0);
    if(texColor.a < 0.1){
        discard;
    }
    gl_FragColor = texColor;
}