#version 330

in vec2 vTexcoord;
in vec4 vColor;

out vec4 outColor;

uniform sampler2D tex;

void main() {

	outColor = texture( tex, vTexcoord );
}