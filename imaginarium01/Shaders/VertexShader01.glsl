#version 400 core


layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUV;

uniform mat4 MVP;


out vec2 coordinate;


void main()
{

    gl_Position =  MVP * vec4(aPos.x, aPos.y,  aPos.z, 1.0);

	coordinate = aUV;

}