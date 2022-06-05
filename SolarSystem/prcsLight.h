#pragma once


namespace LightSource {


	// about light
	struct Light {
		glm::vec4 pos;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec4 att;
	};
	Light light = {
		{ 0.0F, 0.0F, 0.0F, 1.0F},
			{ 0.5f, 0.5f, 0.5f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f, 1.0f },
	};

	struct Material {
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float shineness;
	};
	Material material = {
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		{ 0.8f, 0.8f, 0.8f, 1.0f },
		30.0f,
	};

	void setLnM(GLuint prog) {
		GLuint loc;
		// light
		loc = glGetUniformLocation(prog, "light.pos");
		glUniform4fv(loc, 1, glm::value_ptr(light.pos));
		loc = glGetUniformLocation(prog, "light.ambient");
		glUniform4fv(loc, 1, glm::value_ptr(light.ambient));
		loc = glGetUniformLocation(prog, "light.diffuse");
		glUniform4fv(loc, 1, glm::value_ptr(light.diffuse));
		loc = glGetUniformLocation(prog, "light.specular");
		glUniform4fv(loc, 1, glm::value_ptr(light.specular));
		loc = glGetUniformLocation(prog, "light.att");
		glUniform4fv(loc, 1, glm::value_ptr(light.att));
		// material
		loc = glGetUniformLocation(prog, "material.ambient");
		glUniform4fv(loc, 1, glm::value_ptr(material.ambient));
		loc = glGetUniformLocation(prog, "material.diffuse");
		glUniform4fv(loc, 1, glm::value_ptr(material.diffuse));
		loc = glGetUniformLocation(prog, "material.specular");
		glUniform4fv(loc, 1, glm::value_ptr(material.specular));
		loc = glGetUniformLocation(prog, "material.shineness");
		glUniform1f(loc, material.shineness);
	}

}