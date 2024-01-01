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

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

#define NB_DIRECTIONAL_LIGHT 10
#define NB_POINT_LIGHT 10
#define NB_SPOT_LIGHT 10

#define AMBIENT_STRENGTH 0.1
#define SHININESS 32
#define SPECULAR_STRENGTH 0.5

uniform sampler2D tex;

uniform vec3 viewPos;

uniform int dirLightInUse;
uniform DirectionalLight dirLights[NB_DIRECTIONAL_LIGHT];

uniform int pointLightInUse;
uniform PointLight pointLights[NB_POINT_LIGHT];

uniform int spotLightInUse;
uniform SpotLight spotLights[NB_SPOT_LIGHT];

uniform bool isOutLine;
uniform vec4 outLineColor;

const float levels = 4;

const float celshadingShiness = 1 / levels; 

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir);
vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float CelShadingCalculation(float diff);
float CelShadingSpecCalculation(float levels);
vec3 texCelShading(vec3 diffpos, vec3 normal);

void main(){
	vec4 lightAdditionRes = vec4(0.0);
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	vec4 tex = texture(tex, TexCoord);

    for(int i = 0; i < dirLightInUse; ++i)
	{
        lightAdditionRes += DirLightCalculation(dirLights[i], normal, viewDir);;
	}
    for(int i = 0; i < pointLightInUse; ++i)
	{
        lightAdditionRes += PointLightCalculation(pointLights[i], normal, FragPos, viewDir);
	}
    for(int i = 0; i < spotLightInUse; ++i)
	{
        lightAdditionRes += SpotLightCalculation(spotLights[i], normal, FragPos, viewDir);
	}

	if(isOutLine)
        FragColor = outLineColor;
    else
		FragColor = lightAdditionRes * tex;
}

float CelShadingCalculation(float diff)
{
	return floor(diff * levels) / levels;
}

float CelShadingSpecCalculation(float spec)
{
	return  floor(spec * levels) / levels;
}

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), celshadingShiness);

    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

	diffuse *= CelShadingCalculation(diff);
	ambient  *= CelShadingCalculation(diff);
	specular *= CelShadingSpecCalculation(spec);

    return (ambient + diffuse + specular);
}

vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), celshadingShiness);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
	ambient  *= CelShadingCalculation(diff);
	diffuse *= CelShadingCalculation(diff);
	specular *= CelShadingSpecCalculation(spec);

    return (ambient + diffuse + specular);
}

vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), celshadingShiness);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

	diffuse *= CelShadingCalculation(diff);
	ambient  *= CelShadingCalculation(diff);
	specular *= CelShadingSpecCalculation(spec);

    return (ambient + diffuse + specular);
}