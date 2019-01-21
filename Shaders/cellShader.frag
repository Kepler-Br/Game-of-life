#version 330 core

out vec4 color;
// uniform uint generation;
// uniform uint currentGeneration;
in vec4 fColor;

// vec3(Hue, Saturation, Value)
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	// color = vec3(1,1,0);
	// color = hsv2rgb(vec3((currentGeneration-generation)/100.0f, 1.0f, 1.0f));
	color = fColor;
}