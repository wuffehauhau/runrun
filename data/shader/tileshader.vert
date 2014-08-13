#version 330

uniform mat4 posMatrix;

in vec2 vPosition;
in vec2 vTexCoord;
in vec4 vColorFront;
in vec4 vColorBack;
in vec4 vLight;

out vec2 fTexCoord;
out vec4 fColorFront;
out vec4 fColorBack;

void main()
{
	fTexCoord = vTexCoord;
	
	fColorFront = vColorFront * vLight;
	fColorBack  = vColorBack  * vLight;
	
	gl_Position = posMatrix * vec4(vPosition, 0.0, 1.0);
}

