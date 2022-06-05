#pragma once

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <glm/glm.hpp>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Camera {

	enum what_planet { CAMERA_SUN, CAMERA_MERCURY, CAMERA_VENUS, 
					CAMERA_EARTH, CAMERA_MARS, CAMERA_JUPITER, CAMERA_UP_VIEW = 9 };
	int now = CAMERA_SUN;

	int Camera_status = 0;

#define CAMERA_RIGHT -1
#define CAMERA_LEFT 1
#define CAMERA_PAUSE 0

	// Postion of Camera, Position of Target, view up vector
	glm::vec3 camera_org = glm::vec3(0.0F, 0.0F, 5.0F);
	glm::vec3 camera_now = camera_org;

	glm::vec3 target_org = glm::vec3(0.0F, 0.0F, 0.0F);
	glm::vec3 target_now = target_org;

	glm::vec3 vup_org = glm::vec3(0.0F, 1.0F, 0.0F);
	glm::vec3 vup_now = vup_org;


	// 'mat' for Orginal map
	// 'minimat' for Mini map
	float fovy_org = ((float)M_PI / 180.0F) * 60.0F; // 60 degree , Camera angle
	float fovy = fovy_org;

	glm::mat4 matView = glm::mat4(1.0F);
	glm::mat4 matProj = glm::mat4(1.0F);

	glm::mat4 minimatView = glm::mat4(1.0F);
	glm::mat4 minimatProj = glm::mat4(1.0F);



}