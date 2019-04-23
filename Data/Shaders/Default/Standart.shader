#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;


out VS_OUT {
 vec3 FragPos;
 vec3 Normal;
 vec2 TexCoords;
 vec4 FragPosLight;
} vs_out;

layout(std140) uniform Matrices
{
	mat4 view;
	mat4 projection;
};


uniform mat4 model;
uniform mat4 projViewL;

void main()
{
 vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
 vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
 vs_out.TexCoords = aTexCoords;
 vs_out.FragPosLight = projViewL * vec4(vs_out.FragPos, 1.0);
 gl_Position = projection * view * model * vec4(aPos, 1.0);
}


//=========================================================
#shader fragment
#version 330 core
#define std140 layout (std140)

struct DL;
struct PL;
struct SL;

const int N_DL = 1, N_PL = 1, N_SL = 0;

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

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLight;
} fs_in;

#define FragPos fs_in.FragPos
#define Normal fs_in.Normal
#define TexCoords fs_in.TexCoords
#define FragPosLight fs_in.FragPosLight

uniform sampler2D shadowMap;

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
	uniform vec3 objColor;
	
	vec3 DirectionOut(in DL, in vec3);
	vec3 SpotOut(in SL, in vec3);
	float ShadowCalculation(in vec4);
	vec3 PointOut(in PL, in vec3);
	vec3 texCol(sampler2D);

out vec4 color;

void main()
{
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 result;

	for (int i = 0; i < N_DL; i++) result += DirectionOut(Directional[i], cameraDir);
	//for (int i = 0; i < N_PL; i++) result += PointOut(Point[i], cameraDir);
	//for(int i = 0; i < N_SL; i++) result += SpotOut(Spot[i], cameraDir);

	color = vec4(result*objColor, 1.f);
}

vec3 texCol(sampler2D _texture)
{
	return vec3(texture(_texture, TexCoords));
}

float ShadowCalculation(vec4 fragPosLight)
{
	float shadow = 0.f;
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
	if (projCoords.z > 1.0)
		return 0;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float bias = 0.005;

	/* vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
	for(int y = -1; y <= 1; ++y)
	{
	float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
	shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
	}
	}
	shadow /= 9.0;	*/

	shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}

vec3 DirectionOut(in DL dir,in vec3 cameraDir)
{
	vec3 lightDir = normalize(-dir.direction);
	vec3 ambient = dir.color * _ambient;
	float d = max(dot(lightDir, Normal), 0.f);
	vec3 diffuse = dir.color * _diffuse * d;
	vec3 reflectLight = reflect(-lightDir, Normal);
	float s = pow(max(dot(cameraDir, reflectLight), 0.0), _specularStr)*_specular;
	vec3 specular = s * dir.color;

	float shadow = ShadowCalculation(FragPosLight);
	
	vec3 text_diff = texCol(Textures.texture_diffuse1);
	vec3 text_spec = texCol(Textures.texture_specular1);
		
	ambient *= text_diff;
	diffuse *= (1.f - shadow) * text_diff;
	specular *= (1.f - shadow)* text_spec;
	
	return(ambient + diffuse + specular)* dir.strengh;
}

vec3 PointOut(in PL point,in vec3 cameraDir)
{
	float distance = length(point.position - FragPos);
	float attenuation = 1.0f / (point.Kc + point.Kl*distance + point.Kq*distance*distance);

	vec3 lightDir = normalize(point.position - FragPos);
	vec3 ambient = point.color * _ambient * attenuation;

	float d = max(dot(lightDir, Normal), 0.f) * attenuation;
	vec3 diffuse = point.color * _diffuse * d;
	vec3 reflectLight = reflect(-lightDir, Normal);
	float s = pow(max(dot(cameraDir, reflectLight), 0.0), _specularStr)*_specular*attenuation;
	vec3 specular = s * point.color;
	
	vec3 text_diff = texCol(Textures.texture_diffuse1);
	vec3 text_spec = texCol(Textures.texture_specular1);
		
	ambient *= text_diff;
	diffuse *= text_diff;
	specular *= text_spec;
	
	return (ambient + diffuse + specular)* point.strengh;
}

vec3 SpotOut(in SL spot, in vec3 cameraDir)
{
	vec3 ambient = spot.color * _ambient;

	vec3 lightDir = normalize(spot.position - FragPos);
	float theta = dot(lightDir, normalize(-spot.direction));
	if (theta > spot.outerCutOff) { return ambient; }
	else
	{
		float epsilon = spot.innerCutOff - spot.outerCutOff;
		float intensity = clamp((theta - spot.outerCutOff) / epsilon, 0.0, 1.0);
		vec3 diffuse = spot.color * _diffuse * intensity;
		vec3 reflectLight = reflect(-lightDir, Normal);
		float spec = pow(max(dot(cameraDir, reflectLight), 0.0), _specularStr)*_specular;
		vec3 specular = spec * spot.color * intensity;

		return ((ambient + diffuse) * texCol(Textures.texture_diffuse1) + specular * texCol(Textures.texture_specular1)) * spot.strengh;
	}
}