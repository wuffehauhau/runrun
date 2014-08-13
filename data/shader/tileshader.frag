#version 330

uniform sampler2D texSampler;

in vec2 fTexCoord;
in vec4 fColorFront;
in vec4 fColorBack;

out vec4 colorOut;

void main()
{
	float alpha = texture(texSampler, fTexCoord).r;
	colorOut = alpha * fColorFront + (1.0f - alpha) * fColorBack;
}