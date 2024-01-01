#version 330 core

struct DirectionalLight
{
	vec3 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float innerCutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    mat3 TBN;
} fs_in;

#define NB_DIRECTIONAL_LIGHT 10
#define NB_POINT_LIGHT 10
#define NB_SPOT_LIGHT 10

#define AMBIENT_STRENGTH 0.1
#define SHININESS 32
#define SPECULAR_STRENGTH 0.5

uniform sampler2D tex;
uniform sampler2D normalMap;

uniform int dirLightInUse;
uniform DirectionalLight dirLights[NB_DIRECTIONAL_LIGHT];

uniform int pointLightInUse;
uniform PointLight pointLights[NB_POINT_LIGHT];

uniform int spotLightInUse;
uniform SpotLight spotLights[NB_SPOT_LIGHT];

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir);
vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 tangentFragPos, vec3 viewDir);
vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 tangentFragPos, vec3 viewDir);

void main(){
	vec4 lightAdditionRes = vec4(0.0);

    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

    for(int i = 0; i < dirLightInUse; ++i)
        lightAdditionRes += DirLightCalculation(dirLights[i], normal, viewDir);

    for(int i = 0; i < pointLightInUse; ++i)
        lightAdditionRes += PointLightCalculation(pointLights[i], normal, fs_in.TangentFragPos, viewDir);

    for(int i = 0; i < spotLightInUse; ++i)
        lightAdditionRes += SpotLightCalculation(spotLights[i], normal, fs_in.TangentFragPos, viewDir);

	FragColor = lightAdditionRes * texture(tex, fs_in.TexCoords);
}

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), SHININESS);

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;
    return (ambient + diffuse + specular);
}

vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 tangentFragPos, vec3 viewDir)
{
    vec3 tangentLightPos = fs_in.TBN * light.position;
	vec3 lightDir = normalize(tangentLightPos - tangentFragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), SHININESS);

    float distance = length(tangentLightPos - tangentFragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 tangentFragPos, vec3 viewDir)
{
    vec3 tangentLightPos = fs_in.TBN * light.position;
	vec3 lightDir = normalize(tangentLightPos - tangentFragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), SHININESS);

    float distance = length(tangentLightPos - tangentFragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}