#version 330 core
layout(location = 0) in vec2 vertex;

uniform mat4 cameraMatrix;
uniform int lineX;
uniform int lineY;

void main()
{
	// gl_Position = cameraMatrix*vec4(vec3((vert.x*30.0f+cellX*60.0f), (vert.y*30.0f+cellY*60.0f), 0.0f), 1.0f);
	// vec4 vert = cameraMatrix*vec4(vec3((vertexes.x), (vertexes.y), 0.0f), 0.0f);
	// vec4 pos = cameraMatrix*vec4(lineX, lineY, 0.0f, 1.0f);
	gl_Position = cameraMatrix*vec4(vertex.x, vertex.y, 0.0f, 1.0f);
}