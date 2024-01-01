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
uniform vec4 outLineColor;
uniform bool isOutLine;

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

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir, vec4 tex);
vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 tex);
vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 tex);

void main(){
	vec4 lightAdditionRes = vec4(0.0);

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec4 tex = texture(tex, TexCoord);

    for(int i = 0; i < dirLightInUse; ++i)
        lightAdditionRes += DirLightCalculation(dirLights[i], normal, viewDir,tex);

    for(int i = 0; i < pointLightInUse; ++i)
        lightAdditionRes += PointLightCalculation(pointLights[i], normal, FragPos, viewDir, tex);

    for(int i = 0; i < spotLightInUse; ++i)
        lightAdditionRes += SpotLightCalculation(spotLights[i], normal, FragPos, viewDir, tex);

    if(isOutLine)
        FragColor = outLineColor;
    else
	    FragColor = lightAdditionRes * tex;
}

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir, vec4 tex)
{
    //float kd = 1;
    float a = 0.2;
    float b = 0.6;

	vec3 lightDir = normalize(-light.direction);

    float NL = dot(normalize(normal),lightDir);

    float it = ((1 + NL) / 2);
    vec3 color = (1-it) * (vec3(0, 0, 0.4) + a*tex.xyz) +  it * (vec3(0.4, 0.4, 0) + b*tex.xyz);

    vec3 R = reflect( lightDir,  normalize(normal) );
    float ER = clamp( dot( normalize(viewDir), normalize(R)),0, 1);
    vec4 spec = vec4(1) * pow(ER, SHININESS);

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;

    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;

    return vec4(color + specular.xyz + ambient.xyz , tex.a);
}

vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 tex)
{

    float kd = 1;
    float a = 0.2;
    float b = 0.6;

	vec3 lightDir = normalize(light.position - fragPos);

    float NL = dot(normalize(normal),lightDir);

    float it = ((1 + NL) / 2);
    vec3 color = (1-it) * (vec3(0, 0, 0.4) + a*tex.xyz) +  it * (vec3(0.4, 0.4, 0) + b*tex.xyz);

    vec3 R = reflect( lightDir,  normalize(normal) );
    float ER = clamp( dot( normalize(viewDir), normalize(R)),0, 1);
    vec4 spec = vec4(1) * pow(ER, SHININESS);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;

    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;

    ambient *= attenuation;
    color *= attenuation;
    specular *= attenuation;

    return  vec4(color + specular.xyz + ambient.xyz , tex.a);
}

vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec4 tex)
{
    float kd = 1;
    float a = 0.2;
    float b = 0.6;

	vec3 lightDir = normalize(light.position - fragPos);

    float NL = dot(normalize(normal),lightDir);

    float it = ((1 + NL) / 2);
    vec3 color = (1-it) * (vec3(0, 0, 0.4) + a*tex.xyz) +  it * (vec3(0.4, 0.4, 0) + b*tex.xyz);

    vec3 R = reflect( lightDir,  normalize(normal) );
    float ER = clamp( dot( normalize(viewDir), normalize(R)),0, 1);
    vec4 spec = vec4(1) * pow(ER, SHININESS);
    

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;
    vec4 diffuse = light.diffuse * vec4(color.xyz,0);
    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return  vec4(color + specular.xyz + ambient.xyz , tex.a);
}