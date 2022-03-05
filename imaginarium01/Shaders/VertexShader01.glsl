#version 400 core


layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUV;

out vec3 tstColor;
out vec2 coordinate;


void main()
{

    gl_Position =  vec4(aPos.x, aPos.y,  aPos.z, 1.0);
	tstColor = vec3(aNorm.x,aNorm.y,aNorm.z);
	coordinate = aUV;

}