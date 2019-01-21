#version 330 core

in vec2 uv;
out vec4 fragColor;

uniform bool onPause;
uniform vec2 screenResolution;
uniform sampler2D cfb;
uniform float time;
#define lineWidth 5

void main()
{
    // fragColor = texture(cfb, uv);
    vec4 outCol = vec4(0.0f);

	outCol = texture(cfb, uv);
	if(onPause == false)
	{
		// if (gl_FragCoord.x > screenResolution.x-1)
		// 	fragColor = vec4(1.0f);
		if (gl_FragCoord.x > screenResolution.x-lineWidth)
			outCol += vec4(1.0f) - ((screenResolution.x-gl_FragCoord.x)/lineWidth)*(1.5-((sin(time/500.0)+1.0)/2.0f));

		if (gl_FragCoord.x < lineWidth)
			outCol += vec4(1.0f) - (gl_FragCoord.x/lineWidth)*(1.5-((sin(time/500.0)+1.0)/2.0f));

		if (gl_FragCoord.y > screenResolution.y-lineWidth)
			outCol += vec4(1.0f) - ((screenResolution.y-gl_FragCoord.y)/lineWidth)*(1.5-((sin(time/500.0)+1.0)/2.0f));

		if (gl_FragCoord.y < lineWidth)
			outCol += vec4(1.0f) - (gl_FragCoord.y/lineWidth)*(1.5-((sin(time/500.0)+1.0)/2.0f));
	}
	fragColor = outCol;
	// fragColor = vec4((sin(time/300.0)+1.0)/2.0f);
}