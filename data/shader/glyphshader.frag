#version 330

uniform sampler2D texSampler;

in vec2 fTexCoord;
in vec4 fColor;

out vec4 colorOut;

void main()
{
	float alpha = texture(texSampler, fTexCoord).r;	
	colorOut = alpha * fColor;
}