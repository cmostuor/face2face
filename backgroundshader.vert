#version 130

// vertex positions
in vec3 in_Position;

//texture coordinates
in vec2 in_TexCoords;

//projection matrix
uniform mat4 in_ProjMat;

//view matrix
uniform mat4 in_ViewMat;

//output texture coordinates for fragment shader
out vec2 vs_TexCoords;

void main(void){

	//output vertex positions  
	gl_Position =  in_ProjMat * in_ViewMat * vec4(in_Position,1.0);

	//set texture coordinates for fragment shader
	vs_TexCoords = in_TexCoords;
}