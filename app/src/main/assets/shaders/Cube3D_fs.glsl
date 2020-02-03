precision mediump float;

varying vec3 fColor;

//uniform vec4 textColor;

varying vec4 colorDiffuse;
varying vec3 position;
varying  vec3 normal;


//varying vec4       vMaterialDiffuse;
varying vec3       vMaterialAmbient;
varying vec4       vMaterialSpecular;
varying vec3  vLight0;

void main() {

    vec3 halfVector = normalize(-vLight0 + position);
     float NdotH = max(dot(normalize(normal), halfVector), 0.0);
     float fPower = vMaterialSpecular.w;
     float specular = pow(NdotH, fPower);

    vec4 colorSpecular = vec4( vMaterialSpecular.xyz * specular, 1 );
    gl_FragColor = colorDiffuse + colorSpecular;
    //gl_FragColor = vec4(fColor,1.0);
}