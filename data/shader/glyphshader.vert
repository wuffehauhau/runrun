#version 330

uniform mat4 posMatrix;

in vec2 vPosition;
in vec2 vTexCoord;
in vec4 vColor;

out vec2 fTexCoord;
out vec4 fColor;

void main()
{
	fTexCoord = vTexCoord;
	fColor    = vColor;

	gl_Position = posMatrix * vec4(vPosition, 0.0, 1.0);
}

