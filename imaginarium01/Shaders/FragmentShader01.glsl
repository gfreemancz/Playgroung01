#version 400 core


#define PI 3.1415926538

out vec4 FragColor;


in vec2 coordinate;

uniform sampler2D myTextureSampler;

void main()
{

	
    FragColor = vec4(texture( myTextureSampler, coordinate ).rgb, 1.0f);

} 