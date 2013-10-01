#version 400

in vec4 Position;
in vec2 UV;

out vec4 vWorldPosition;
out vec4 vScreenPosition;
out vec2 vUV;
out vec4 vCol;

uniform sampler2D diffuseTexture;
//uniform sampler2D normalTexture;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

void main()
{
	vUV = UV;

	vWorldPosition	= Position;
	vWorldPosition.y += sin(Time + Position.z)*0.15;
	vWorldPosition.y += sin(Time + Position.x)*0.15;

	//vWorldPosition.z = cos(Time + Position.y) ;
	//vWorldPosition.z = sin(Time + Position.x);
	//vWorldPosition.z = vWorldPosition.z + sin(Time) * sin(Position.x);

	vScreenPosition	= Projection * View * Model * vWorldPosition;
	

	gl_Position = vScreenPosition; //Projection * View * Model * Position;

	
	
	//vec3 N;
	//N.x = 2 *( texture2D( normalTexture, vUV ).x ) -1;
	//N.y = 2 *( texture2D( normalTexture, vUV ).y ) -1;
	//N.z = 2 *( texture2D( normalTexture, vUV ).z ) -1;

	//vec3 lightPos = vec3(0,4,0);
	//vec3 L = normalize( lightPos - Position.xyz );

	//float NdotL = dot(N, L);
	//vCol = texture2D(diffuseTexture, vUV) * vec4(max(0.0, NdotL));
	//vCol = vec4(1, 0, 0, 1);// + texture2D(diffuseTexture, vUV);
	//vCol = texture2D( diffuseTexture, vUV ).bgra;
}
