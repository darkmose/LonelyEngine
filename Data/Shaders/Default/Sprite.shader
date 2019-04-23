#shader vertex
#version 330 core
layout (location = 0) in vec3 pos; 
layout (location = 1) in vec2 textPos;

layout (std140) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

uniform mat4 model;

out vec2 TexPos;

void main()
{
	TexPos = textPos;
	gl_Position = projection * view * model * vec4(pos.xy,0,1);
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
	
	uniform float transparent;
	uniform Texture Textures;
	uniform vec3 col;
	
void main()
{
    vec4 texColor = texture(Textures.texture_diffuse1, TexPos);
    if(texColor.a < 0.01)
        discard;
    color = texColor * vec4(col,transparent);
}

