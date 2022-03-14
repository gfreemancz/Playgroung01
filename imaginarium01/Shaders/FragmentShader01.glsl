#version 400 core

out vec4 FragColor;

//uniform vec4 ourColor;

in vec3 tstColor;
#define PI 3.1415926538
//in float testik;
in vec2 coordinate;

void main()
{
    FragColor = vec4(tstColor.x, tstColor.y, tstColor.z, 1.0f);
    //FragColor = vec4(sin(coordinate.x*PI*3), sin(coordinate.y*PI*3), 0, 1.0f);
} 