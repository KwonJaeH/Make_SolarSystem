#pragma once
#pragma once
#include <stdio.h>
#include <glm/glm.hpp>

namespace Sphere {

	void triangles(int level, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c);
	void generateSphere(int level);

	int levelSphere;
	int numVertSphere = 0;
	glm::vec4 vertSphere[10240];
	glm::vec4 normSphere[10240];
	int colorIdx[10240];


	glm::vec4 LightnormSphere[10240];

	void triangles(int level, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c) {
		if (numVertSphere >= sizeof(vertSphere) / sizeof(vertSphere[0])) {
			//vertex buffer overflow
			return;
		}
		if (level <= 0) {
			vertSphere[numVertSphere] = glm::vec4(a.x, a.y, a.z, 1.0F);
			vertSphere[numVertSphere + 1] = glm::vec4(b.x, b.y, b.z, 1.0F);
			vertSphere[numVertSphere + 2] = glm::vec4(c.x, c.y, c.z, 1.0F);


			normSphere[numVertSphere] = glm::vec4(a.x, a.y, a.z, 1.0F);
			normSphere[numVertSphere + 1] = glm::vec4(b.x, b.y, b.z, 1.0F);
			normSphere[numVertSphere + 2] = glm::vec4(c.x, c.y, c.z, 1.0F);
			
			LightnormSphere[numVertSphere] = glm::vec4(a.x, a.z, a.y, 1.0F);
			LightnormSphere[numVertSphere + 1] = glm::vec4(b.x, b.z, b.y, 1.0F);
			LightnormSphere[numVertSphere + 2] = glm::vec4(c.x, c.z, c.y, 1.0F);

			int color_idx = rand() % 6;

			colorIdx[numVertSphere] = color_idx;
			colorIdx[numVertSphere + 1] = color_idx;
			colorIdx[numVertSphere + 2] = color_idx;

			numVertSphere += 3;
		}
		else {

			glm::vec3 ab = normalize(a + b);
			glm::vec3 bc = normalize(b + c);
			glm::vec3 ca = normalize(c + a);

			// call sub-triangles

			triangles(level - 1, a, ab, ca);
			triangles(level - 1, b, bc, ab);
			triangles(level - 1, c, ca, bc);
			triangles(level - 1, ab, bc, ca);
		}
	}

	void generateSphere(int level) {
		static glm::vec3 v[6] = {
			{ +1, 0, 0 },
			{ 0, +1, 0 },
			{ -1, 0, 0 },
			{ 0, -1, 0 },
			{ 0, 0, +1 },
			{ 0, 0, -1 },
		};
		numVertSphere = 0;
		triangles(level, v[0], v[1], v[4]);
		triangles(level, v[1], v[2], v[4]);
		triangles(level, v[2], v[3], v[4]);
		triangles(level, v[3], v[0], v[4]);
		triangles(level, v[1], v[0], v[5]);
		triangles(level, v[2], v[1], v[5]);
		triangles(level, v[3], v[2], v[5]);
		triangles(level, v[0], v[3], v[5]);
		//printf("totally %d vertices\n", numVertSphere);
	}
}
