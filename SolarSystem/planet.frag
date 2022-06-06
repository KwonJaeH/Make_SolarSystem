#version 330 core

in vec4 vColor; // varying color: varing
out vec4 FragColor; // fragment color: framebuffer

in vec4 vPos;
in vec4 vNorm;

uniform int Is_lightSource;


in vec2 TexCoord;
uniform sampler2D ourTexture;
in vec4 texpos;

struct Light {
	vec4 pos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 att;
};
uniform Light light;

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shineness;
};
uniform Material material;

void main(void) {
	
	vec2 longi = vec2((atan(texpos.x, texpos.z) / 3.1415926 + 1.0)*0.5, 
				(asin(texpos.y) / 3.1415926 + 0.5));
	
	if (Is_lightSource == 1){
		//FragColor = vColor;
		FragColor = texture(ourTexture, longi);
	}else{
		vec3 N = normalize(vNorm.xyz);
		vec3 L = normalize(light.pos.xyz - vPos.xyz);
		vec3 V = vec3(0.0F, 0.0F, 1.0F);
		vec3 H = normalize(L + V);
		vec4 ambient = light.ambient * material.ambient;
		float d = length(light.pos.xyz - vPos.xyz);
		float denom = light.att.x + light.att.y * d + light.att.z * d * d;
		vec4 diffuse = max(dot(L, N), 0.0) * light.diffuse * material.diffuse / denom;
		vec4 specular = pow(max(dot(N, H), 0.0), 3 * material.shineness) * light.specular * material.specular / denom;
		//FragColor = (ambient + diffuse + specular) * vColor;
		FragColor = (ambient + diffuse + specular) * texture(ourTexture, longi);
	}
}
