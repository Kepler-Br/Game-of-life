#version 330 core
layout(location = 0) in vec3 vertexes;

uniform mat4 cameraMatrix;
uniform int cellX;
uniform int cellY;
uniform uint generation;
uniform uint currentGeneration;

out vec4 fColor;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec3 vert = vertexes;
	// gl_Position = cameraMatrix*vec4(vec3((vert.x*30.0f+cellX*60.0f), (vert.y*30.0f+cellY*60.0f), 0.0f), 1.0f);
	gl_Position = cameraMatrix*vec4(vec3((vert.x+cellX), (vert.y+cellY), 0.0f), 1.0f);
	fColor = vec4(hsv2rgb(vec3((currentGeneration-generation)/100.0f, 1.0f, 1.0f)), 1.0f);
}