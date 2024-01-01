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

vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir,vec4 tex);
vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec4 tex);
vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec4 tex);
vec4 GoochShading(vec4 color,vec3 lightDirection,vec3 normal,vec3 camDirection);


void main(){
	vec4 lightAdditionRes = vec4(0.0);

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec4 tex = texture(tex, TexCoord);

    for(int i = 0; i < dirLightInUse; ++i)
        lightAdditionRes += DirLightCalculation(dirLights[i], normal, viewDir, tex);

    for(int i = 0; i < pointLightInUse; ++i)
        lightAdditionRes += PointLightCalculation(pointLights[i], normal, FragPos, viewDir, tex);

    for(int i = 0; i < spotLightInUse; ++i)
        lightAdditionRes += SpotLightCalculation(spotLights[i], normal, FragPos, viewDir, tex);

	FragColor = lightAdditionRes;
}


vec4 GoochShading(vec4 color,vec3 lightDirection,vec3 normal,vec3 camDirection)
{
    float kd = 1;
    float a = 0.2;
    float b = 0.6;
    
    float dotn = dot(normalize(normal),normalize(lightDirection));

    float it = ((1 + dotn) / 2);

    vec3 m_color = (1-it) * (vec3(0, 0, 0.4) + a*color.xyz);

    vec3 R = reflect( -normalize(lightDirection), normalize(normal) );

     float ER = clamp( dot( normalize(camDirection), normalize(R)),0, 1);

     vec4 spec = vec4(1) * pow(ER, SHININESS);

     return vec4(m_color + spec.xyz, color.a);
}


vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir, vec4 tex)
{
    float kd = 1;
    float a = 0.2;
    float b = 0.6;
    

	vec3 lightDir = normalize(-light.direction);

    float dotn = dot(normalize(normal),normalize(lightDir));
    float it = ((1 + dotn) / 2);
    vec3 m_color = (1-it) * (vec3(0, 0, 0.4) + a*tex.xyz);
    vec3 R = reflect( -normalize(lightDir), normalize(normal) );
     float ER = clamp( dot( normalize(viewDir), normalize(R)),0, 1);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), SHININESS);

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = (vec4(1) * pow(ER, SHININESS))*spec;
    return ((m_color + specular.xyz)*(m_color + ambient.xyz)*(m_color + diffuse.xyz), tex);
}

vec4 PointLightCalculation(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec4 tex)
{
	vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), SHININESS);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec4 SpotLightCalculation(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec4 tex)
{
	vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), SHININESS);

    float distance = length(light.position - fragPos);
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