attribute vec3 aPosition;
attribute vec2 aTexture;
varying vec2 vTexture;

void main()
{
    gl_Position =  vec4(aPosition,-15.0);
    vTexture = aTexture;
}