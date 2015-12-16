#version 130

in vec2 vs_TexCoords;
out vec4 out_Color;

uniform sampler2D tex;

void main(void){
	out_Color = texture(tex, vs_TexCoords);
	float red = out_Color.x;
	out_Color.x = out_Color.z;
	out_Color.z = red;
}