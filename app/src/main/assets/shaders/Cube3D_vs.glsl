
attribute vec3 vPosition;
attribute vec3 vColor;
attribute vec3 vNormal;


uniform mat4 P;
uniform mat4 M;
uniform mat4 V;
uniform mat4 MVP;

varying vec3 FragPos;
varying vec3 Normal;
varying vec3 LightPos;
varying vec3 fColor;

varying vec4 colorDiffuse;
varying vec3 position;
varying  vec3 normal;

varying vec4       vMaterialDiffuse;
varying vec3       vMaterialAmbient;
varying vec4       vMaterialSpecular;

varying vec3  vLight0;


void main() {

        vMaterialDiffuse = vec4(vColor, 1.0);//vec4(1.0, 0.5, 0.5, 1.0);
        //vMaterialDiffuse = vec4(1.0, 0.5, 0.5, 1.0);
        vMaterialAmbient = vec3(0.1, 0.1, 0.1);
        vMaterialSpecular = vec4(1.0, 1.0, 1.0, 100.0);
        //vLight0 = vec3(100.0, -200.0, -600.0);
        vLight0 = vec3(0.0, 0.0, -500.0);

    vec4 p = vec4(vPosition,1);
    gl_Position = P * V * M * p;
    mat4      uMVMatrix = V * M;

    vec3 worldNormal = vec3(mat3(uMVMatrix[0].xyz, uMVMatrix[1].xyz, uMVMatrix[2].xyz) * vNormal);
    vec3 ecPosition = p.xyz;

    colorDiffuse = dot( worldNormal, normalize(-vLight0+ecPosition) ) * vMaterialDiffuse  + vec4( vMaterialAmbient, 1 );

    normal = worldNormal;
    position = ecPosition;
    fColor = vColor;
    /*

    float ambientForce = 0.6;
    vec3 lightColor = vec3(0.8, 0.8 , 0.8);

    vec3 ambientLight = ambientForce * lightColor;


    vec3 u_LightPos = vec3(0.0,0.0,10.0);

    vec3 modelViewVertex = vec3(MVP * vec4(vPosition, 1.0));
    vec3 modelViewNormal = vec3(V*M * vec4(vNormal, 1.0));
    float distance = length(u_LightPos - modelViewVertex);
    vec3 lightVector = normalize(u_LightPos - modelViewVertex);
    float diffuse = max(dot(modelViewNormal, lightVector), 0.0);

    //diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));


    gl_Position =  P * V * M * vec4(vPosition, 1.0);
    //vColor = vec3(1.0,0.0,0.0);
    fColor =  (+diffuse)*vec3(1.0,0.0,0.0);


    */
}
