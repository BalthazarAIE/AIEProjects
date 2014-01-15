#version 330

in vec4 position;
in vec2 texcoord;
in vec4 color;


out vec2 vTexcoord;
out vec4 vColor;


void main() {
	vTexcoord = texcoord ;
	vColor = position;
	gl_Position = position;
}