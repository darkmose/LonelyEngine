#shader vertex
#version 330 core

#define std140 layout (std140)

layout (location = 0) in vec3 pos; 
layout (location = 1) in vec2 textPos;
layout (location = 2) in vec3 normal;

std140 uniform Matrices
{
	mat4 view;
	mat4 projection;
};

out VS_OUT
{
	vec2 TexturePos;
	vec3 FragPos;
	vec3 Normal;	
}vs_o;



uniform mat4 model;
uniform vec2 offset;
uniform vec2 stretch;

void main()
{
	vs_o.FragPos = vec3(model*vec4(pos,1));
	vs_o.Normal = normalize(normal);
	gl_Position = projection * view * model * vec4(pos,1);
	vs_o.TexturePos = vec2(textPos.x*stretch.x+offset.x, textPos.y*stretch.y+offset.y);
}

///////////////////////////////////////////////////////////////////////////////////

#shader fragment
#version 330 core
#define std140 layout (std140)


in VS_OUT
{
	vec2 TexturePos;
	vec3 Normal;
	vec3 FragPos;
}vs_i;

#define TexturePos vs_i.TexturePos
#define Normal vs_i.Normal
#define FragPos vs_i.FragPos

struct DL;
struct PL;
struct SL;

const int N_DL=1,N_PL=0,N_SL=0;

std140 uniform MatProps
{
	float _ambient;
	float _diffuse;
	float _specular;
	float _specularStr;
	vec3 cameraPos;
};

std140 uniform Light
{
	//PL Point[N_PL];
	DL Directional[N_DL];
	//SL Spot[N_SL];
};

struct Texture
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
};
	
struct DL
{
	vec3 direction;
	vec3 color;	
	float strengh;
};
	
struct PL
{
	vec3 position;
	vec3 color;
	float strengh;
	float Kc;
	float Kl;
	float Kq;
};
	
struct SL
{
	vec3 position;
	vec3 color;
	vec3 direction;
	float strengh;
	float innerCutOff;
	float outerCutOff;
};

uniform Texture Textures;

vec3 DirectionOut(in DL,in vec3);
vec3 SpotOut(in SL,in vec3);
vec3 PointOut(in PL,in vec3);
vec3 texCol(sampler2D);

out vec4 color;

void main()
{
    vec3 cameraDir = normalize(cameraPos - FragPos);
    vec3 result;
    
	for(int i = 0; i < N_DL; i++) result += DirectionOut(Directional[i], cameraDir);
	//for(int i = 0; i < N_PL; i++) result += PointOut(Point[i], cameraDir);
	//for(int i = 0; i < N_SL; i++) result += SpotOut(Spot[i], cameraDir);
    
    color = vec4(result,1.f);
}

vec3 texCol(sampler2D _texture)
{
	return vec3(texture(_texture, TexturePos));
}

vec3 DirectionOut(in DL dir,in vec3 cameraDir)
{
	vec3 lightDir = normalize(-dir.direction);
	vec3 ambient = dir.color * _ambient;
	float d = max(dot(lightDir,Normal),0.f);
	vec3 diffuse = dir.color * _diffuse * d;
	vec3 reflectLight = reflect(-lightDir, Normal);
	float s = pow(max(dot(cameraDir, reflectLight), 0.0), _specularStr)*_specular;
	vec3 specular = s * dir.color;
	
	vec3 text_diff = texCol(Textures.texture_diffuse1);
	vec3 text_spec = texCol(Textures.texture_specular1);
		
	ambient *= text_diff;
	diffuse *=text_diff;
	specular *= text_spec;
	
	return (ambient + diffuse + specular)* dir.strengh;
}

vec3 PointOut(in PL point,in vec3 cameraDir)
{
	float distance = length(point.position - FragPos);
	float attenuation = 1.0f/(point.Kc + point.Kl*distance + point.Kq*distance*distance);
	
	vec3 lightDir = normalize(point.position - FragPos);
	vec3 ambient = point.color * _ambient * attenuation;
	
	float d = max(dot(lightDir,Normal),0.f) * attenuation;
	vec3 diffuse = point.color * _diffuse * d ;
	vec3 reflectLight = reflect(-lightDir, Normal);
	float s = pow(max(dot(cameraDir, reflectLight), 0.0), _specularStr)*_specular*attenuation;
	vec3 specular = s * point.color;
	
	return ((ambient + diffuse) * texCol(Textures.texture_diffuse1) + specular*texCol(Textures.texture_specular1))* point.strengh;
}

vec3 SpotOut(in SL spot,in vec3 cameraDir)
{
	vec3 ambient = spot.color * _ambient;	
	
	vec3 lightDir = normalize(spot.position - FragPos);
	float theta = dot(lightDir, normalize(-spot.direction));
	if(theta > spot.outerCutOff){return ambient;}
	else
	{
		float epsilon = spot.innerCutOff - spot.outerCutOff;
		float intensity = clamp((theta - spot.outerCutOff) / epsilon, 0.0, 1.0);
		vec3 diffuse = spot.color * _diffuse * intensity;
		vec3 reflectLight = reflect(-lightDir, Normal);
		float spec = pow(max(dot(cameraDir, reflectLight), 0.0), _specularStr)*_specular;
		vec3 specular = spec * spot.color * intensity;
		
		return ((ambient + diffuse) * texCol(Textures.texture_diffuse1) + specular*texCol(Textures.texture_specular1)) * spot.strengh;
	}	
}