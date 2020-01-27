
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

void main() {

    vec3 u_LightPos = vec3(0.0,0.0,0);

    vec3 modelViewVertex = vec3(MVP * vec4(vPosition, 1.0));
    vec3 modelViewNormal = vec3(V*M * vec4(vNormal, 1.0));
    float distance = length(u_LightPos - modelViewVertex);
    vec3 lightVector = normalize(u_LightPos - modelViewVertex);
    float diffuse = max(dot(modelViewNormal, lightVector), 0.1);

    diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));


    gl_Position =  P * V * M * vec4(vPosition, 1.0);

    fColor = vColor * diffuse;;
}
