#version 150
//Phong Vertex Shader

// vertex positions
in vec3 in_Position;

//vertex normals
in vec3 in_Normals;

//texture coordinates
in vec2 in_TexCoords;

//projection matrix
uniform mat4 in_ProjMat;

//view matrix
uniform mat4 in_ViewMat;

//model matrix
uniform mat4 in_ModelMat;

//normals matrix
uniform mat3 in_NormalMat;

out VertexData
{
//output position for light vector calculation
vec4 vs_Position;

//output normal vector
vec3 vs_Normals;

//output texture coordinates for fragment shader
vec2 vs_TexCoords;
} outData;

void main(void){
	//pass on position
	outData.vs_Position = in_ModelMat * vec4(in_Position,1.0);

	//output vertex positions
	mat4 mvp = in_ProjMat * in_ViewMat * in_ModelMat;
	gl_Position = mvp * vec4(in_Position,1.0);

	//get normal vectors
	outData.vs_Normals = mat3(in_ViewMat * in_ModelMat) * in_Normals;

	//set texture coordinates for fragment shader
	outData.vs_TexCoords = in_TexCoords;
}