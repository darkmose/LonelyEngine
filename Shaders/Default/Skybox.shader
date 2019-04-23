#shader vertex
#version 330 core
layout (location = 0) in vec3 pos; 
layout (std140) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

out vec3 TexPos;

void main()
{
	TexPos = pos;
	vec4 poss = projection * mat4(mat3(view)) * vec4(pos,1.f);
	gl_Position = poss.xyww;
}


//=============================================================

#shader fragment
#version 330 core

in vec3 TexPos;
out vec4 color;
uniform samplerCube cubeMap;

void main()
{
	color = texture(cubeMap,TexPos);
}
