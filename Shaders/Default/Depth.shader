#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projView;
uniform mat4 model;
void main()
{
 gl_Position = projView * model * vec4(aPos, 1.0); 
}
//=============================================
#shader fragment
#version 330 core
	
void main()
{

}


