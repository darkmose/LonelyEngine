#shader vertex
#version 330 core
layout (location = 0) in vec2 aPos; 
layout (location = 1) in vec2 texPos;

out vec2 TexPos;

void main()
{
	TexPos = texPos;
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
}


//================================================
#shader fragment
#version 330 core
in vec2 TexPos;

out vec4 color;

	struct Texture
	{
		sampler2D main;	
	};

	uniform Texture Textures;
	uniform int _case;
	const float offset = 1.0 / 300.0;  

void main()
{
	if(_case == 0)
		color = texture(Textures.main, TexPos);
	if(_case == 1)
	{
		color = vec4(vec3(1-texture(Textures.main, TexPos)),1.f);
	}
	if(_case == 2)
	{
	    color = texture(Textures.main, TexPos);
		float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b + 0.1;
		color = vec4(average, average, average, 1.0);
	}
	if(_case == 3){
		vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
		);

		float kernel[9] = float[](
			0.0625, 0.125, 0.0625,
			0.125,  0.25, 0.125,
			0.0625, 0.125, 0.0625
		);
		
		vec3 sampleTex[9];
		for(int i = 0; i < 9; i++)
		{
			sampleTex[i] = vec3(texture(Textures.main, TexPos.st + offsets[i]));
		}
		vec3 col = vec3(0.0);
		for(int i = 0; i < 9; i++)
			col += sampleTex[i] * kernel[i];
    
		color = vec4(col, 1.0);
	}
}

