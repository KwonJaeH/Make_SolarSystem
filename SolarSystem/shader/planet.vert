#version 330 core

in vec4 aPos; // vertex position: attribute
in vec4 aNorm;
out vec4 vPos;
out vec4 vNorm;

in vec4 aColor; // vertex color: attribute
out vec4 vColor; // varying color: varying

uniform mat4 uModel; // model matrix: uniform
uniform mat4 uView; // view matrix: uniform
uniform mat4 uProj; // projection matrix: uniform

uniform int Is_lightSource;


in vec2 aTexCoord;
out vec2 TexCoord;
out vec4 texpos;

void main(void) {
	texpos = aPos;
	TexCoord = aTexCoord;
	
	if (Is_lightSource == 1)
		gl_Position = uProj * uView * uModel * aPos;
	else{ 
		mat4 uMat = uProj * uView * uModel;
		vPos = uMat * aPos; // transformation
		vNorm = transpose(inverse(uProj*uModel)) * aNorm; // normal vector in view frame
		gl_Position = vPos;
	}	

	//gl_Position = uProj * uView * uModel * aPos;
	vColor = aColor;

	//lightSource = Is_lightSource;
}
