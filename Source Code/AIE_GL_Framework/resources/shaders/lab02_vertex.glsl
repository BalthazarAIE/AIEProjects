#version 400

in vec4 Position;
in vec2 UV;

out vec4 vWorldPosition;
out vec4 vScreenPosition;
out vec2 vUV;

uniform sampler2D diffuseTexture;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Distance;

uniform float Time;

void main()
{
	vUV = UV;

	vWorldPosition	= Position;

	if( Distance < 50 )
		vWorldPosition.y += sin(Time + vWorldPosition.x*0.04);
	else if( Distance < 90 )
	{
		float dist = Distance;
		dist = (dist - 50)/ 40;
		vWorldPosition.y += sin(Time + vWorldPosition.x*0.04) * (1 - dist);
	}

	vScreenPosition	= Projection * View * Model * vWorldPosition;
	
	gl_Position = vScreenPosition;
}
