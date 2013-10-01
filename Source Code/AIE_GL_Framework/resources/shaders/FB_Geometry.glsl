#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 vPosition[];
in vec2 vUV[];

out vec4 gPosition;
out vec2 gUV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

uniform mat4 CameraMat;

void main()
{
	gl_Position = vPosition[0];
	gUV = vUV[0];
	EmitVertex();

	gl_Position = vPosition[1];
	gUV = vUV[1];
	EmitVertex();

	gl_Position = vPosition[2];
	gUV = vUV[2];
	EmitVertex();

	EndPrimitive();
}