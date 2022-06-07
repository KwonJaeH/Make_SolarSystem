#pragma once
#include <glm/glm.hpp>

float sun_radius = 0.0F;
float sun_axis = 0.0F;
glm::vec3 sun_scale = glm::vec3(0.8F, 0.8F, 0.8F);
glm::vec4 SunColor[] = {
	// v0 ~ v6 , color
	{1.0F, 0.0F, 0.0F, 1.0F}, //red
	{1.0F, 1.0F, 0.0F, 1.0F}, // yellow
	{1.0F, 0.843137F, 0.5F, 1.0F}, // gold
	{1.0F, 0.843137F, 0.5F, 1.0F}, // gold
	{1.0F, 0.647959F, 0.0F, 1.0F}, // orange
	{1.0F, 0.0F, 0.0F, 1.0F} //red
};


float mercury_radius = 1.2F;
float mercury_axis = 0.0F;
glm::vec3 mercury_scale = glm::vec3(0.05F, 0.05F, 0.05F);

float venus_radius = 1.7F;
float venus_axis = 0.0F;
glm::vec3 venus_scale = glm::vec3(0.08F, 0.08F, 0.08F);

float earth_radius = 2.2F;
float earth_axis = (float)M_PI / 180 * 23.5;
glm::vec3 earth_scale = glm::vec3(0.1F, 0.1F, 0.1F);
glm::vec4 EarthColor[] = {
	// v0 ~ v6 , color
	{0.0F, 0.74902F, 1.0F, 1.0F}, //Deep Sky blue
	{0.0F, 0.0F, 1.0F, 1.0F},  // blue
	{0.12549F, 0.698039F, 0.66667F, 1.0F}, // light see green
	{0.0F, 1.0F, 0.0F, 1.0F},   // green
	{0.0F, 0.807843F, 0.980392F, 1.0F},  // sky blue
	{0.0F, 0.74902F, 1.0F, 1.0F} //Deep Sky blue
};

float moon_radius = 0.2F;
float moon_axis = 0.0F;
glm::vec3 moon_scale = glm::vec3(0.02F, 0.02F, 0.02F);
glm::vec4 MoonColor[] = {
	// v0 ~ v6 , color
	{1.0F, 1.0F, 1.0F, 1.0F}, // white
	{0.827451F, 0.827451F, 0.827451F, 1.0F},  // light gray
	{0.745098F, 0.745098F, 0.745098F, 1.0F}, // gray
	{0.745098F, 0.745098F, 0.745098F, 1.0F},  // gray
	{0.745098F, 0.745098F, 0.745098F, 1.0F},  // gray
	{1.0F, 1.0F, 1.0F, 1.0F} // white
};

float mars_radius = 2.6F;
float mars_axis = 0.0F;
glm::vec3 mars_scale = glm::vec3(0.08F, 0.08F, 0.08F);
glm::vec4 MarsColor[] = {
	// v0 ~ v6 , color
	{0.737255F, 0.560784F, 0.560784F, 1.0F}, // Rosy Brown
	{0.803922F, 0.360784F, 0.360784F, 1.0F},  // Indian Red
	{0.647059, 0.164706F, 0.164706F, 1.0F}, // Brown
	{0.545098, 0.270588F, 0.07451F, 1.0F},  // Saddle Brown
	{0.803922F, 0.360784F, 0.360784F, 1.0F},  //
	{0.737255F, 0.560784F, 0.560784F, 1.0F} // Rosy Brown
};


float jupiter_radius = 4.0F;
float jupiter_axix = 0.0F;
glm::vec3 jupiter_scale = glm::vec3(0.2F, 0.2F, 0.2F);
glm::vec4 JupiterColor[] = {
	{0.960784F, 0.960784F, 0.862745F, 1.0F},  // Beige
	{0.870588F, 0.721569F, 0.529412F, 1.0F}, // Burlywood
	{0.870588F, 0.721569F, 0.529412F, 1.0F}, // Burlywood
	{0.870588F, 0.721569F, 0.529412F, 1.0F}, // Burlywood
	{0.960784F, 0.960784F, 0.862745F, 1.0F},  // Beige
	{0.870588F, 0.721569F, 0.529412F, 1.0F} // Burlywood
};

