#version 150
//Phong Fragment Shader a la lensch

vec3 LightPosition = vec3(5.0, 3.0, -5.0);
vec3 LightColor = vec3(1.0, 1.0, 1.0);

uniform vec4 in_diffuse;
uniform vec4 in_specular;

in VertexData
{
//input position for light vector calculation
vec4 vs_Position;

//input normal vector
vec3 vs_Normals;

//input texture coordinates for fragment shader
vec2 vs_TexCoords;
} inData;

uniform sampler2D tex;
uniform mat4 in_LightMatrix;

out vec4 outColor;
void main(void)
{
	vec3 texColor = vec3(texture(tex, inData.vs_TexCoords));
	LightPosition = vec3(in_LightMatrix * vec4(LightPosition, 1.0));
	vec3 LightDirection = vec3(inData.vs_Position) - LightPosition;
	vec3 toViewer = normalize(-vec3(inData.vs_Position));
	vec3 toLight = normalize(-LightDirection);
	
	vec3 halfVector = normalize(toViewer + toLight);
	
	vec3 normal = normalize(inData.vs_Normals);
	vec3 diffuse = vec3(in_diffuse) * texColor * LightColor * max(0.0, dot(normal, -LightDirection));
	vec3 specular = vec3(in_specular) * LightColor * max(0.0, pow(dot(halfVector, normal), 1000.0));
	
	outColor = vec4(diffuse+specular, 1.0);
}