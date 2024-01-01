#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;

out VS_OUT {
    vec2 TexCoords;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    mat3 TBN;
} vs_out;

uniform mat4 mvp;
uniform mat4 model;
uniform vec3 viewPos;

void main(){
	gl_Position = mvp * vec4(aPos, 1.0);
	vs_out.TexCoords = aTexCoord;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    vs_out.TBN = transpose(mat3(T, B, N));

    vs_out.TangentViewPos  = vs_out.TBN * viewPos;
    vs_out.TangentFragPos  = vs_out.TBN * vec3(model * vec4(aPos, 1.0));
}