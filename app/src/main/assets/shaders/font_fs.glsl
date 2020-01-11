precision mediump float;
varying vec2 TexCoords;

uniform sampler2D text;
uniform vec3 textColor;


void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, TexCoords).r);

    if(sampled.a < 0.5){
        discard;
    }
    //textColor = vec3(0.1, 0.8, 0.2);
    //mediump float sampled = texture2D(text, TexCoords).r;
    //vec4 texColor = texture2D(uTexture, TexCoords);
    gl_FragColor = vec4(textColor, 1.0)*sampled;//vec4(textColor, 1.0) * sampled;
}