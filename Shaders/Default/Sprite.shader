#shader vertex
#version 330 core
layout (location = 0) in vec2 pos; 
layout (location = 1) in vec2 textPos;

layout (std140) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

struct MatrixMVP
{
	mat4 model;
};
uniform MatrixMVP Matrix;

out vec2 TexPos;

void main()
{
	TexPos = textPos;
	gl_Position = projection * view * Matrix.model * vec4(pos,0,1);
}


//===============================================================
#shader fragment
#version 330 core
in vec2 TexPos;


out vec4 color;

	struct Texture
	{
		sampler2D texture_diffuse1;	
	};
	
	uniform float transparent = 1;
	uniform Texture Textures;
	uniform vec3 col;
	
void main()
{
    vec4 texColor = texture(Textures.texture_diffuse1, TexPos);
    if(texColor.a < 0.05)
        discard;
    color = texColor * vec4(col,transparent);
}

