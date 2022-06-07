#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>
using namespace std;

namespace texture {

	unsigned int texture_idx[9];
	enum planet_name {SUN, MERCURY, VENUS, EARTH, MOON, MARS, JUPITER};
	string fileNameOfPlanet[] = { "sun","mercury","venus","earth","moon","mars","jupiter" };
	
	int planet_cnt = 7;

	void CreateTexture() {
		glGenTextures(planet_cnt, texture_idx);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		for (int i = 0; i < planet_cnt; i++) {
			int width, height, nrChannels;
			
			glBindTexture(GL_TEXTURE_2D, texture_idx[i]);
			string textureFilename = "./image/" + fileNameOfPlanet[i] + ".jpg";
			cout << textureFilename << "\n";
			unsigned char* data = stbi_load(textureFilename.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture" << std::endl;
			}
			stbi_image_free(data);
		}
	}

	void usePlanetImage(int planet_enum_idx) {
		glBindTexture(GL_TEXTURE_2D, texture_idx[planet_enum_idx]);
	}
}