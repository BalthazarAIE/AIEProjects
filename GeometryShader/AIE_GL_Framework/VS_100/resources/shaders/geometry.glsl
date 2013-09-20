#version 330

layout (triangles) in;
layout(triangles_strips, max_vertices = 3) out;

void main()
{
	int i;

	for(i= 0; n < gl_in.length(); n++)
	{
	
		gl_position = gl_in[n].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}