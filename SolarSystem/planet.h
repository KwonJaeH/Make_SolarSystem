#pragma once
#ifndef __cplusplus
#error This file works only with C++
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

#pragma warning(disable: 4711 4710 4100 4514 4626 4774 4365 4625 4464 4571 4201 5026 5027 5039)

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp> // for glm::to_string()
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr( )

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma warning(disable: 4711 4710 4100)

class Planet {

protected:
	glm::vec4 sphereColor[10240];
	glm::vec4 vertColor[6];

	glm::mat4 ModelMat = glm::mat4(1.0F);
	glm::vec3 thisScale;

	float radius;
	float axis_angle;
	
	#define DEFAULT_SEC 1
	float orbit_theta, rotate_theta;
	float orbit_sec, rotate_sec;


	
	float camera_theta = 0.0F;
	float camera_radius = 0.5F;
	glm::vec3 camera_position;
	glm::vec3 camera_vup;

	

	glm::vec3 planet_position;

public:
	Planet() {}
	Planet(float rad, float ax_ang, glm::vec3 scale_of) {
		// Input Planet radius, axix angle, size
		radius = rad;
		axis_angle = ax_ang;
		thisScale = scale_of;
	}

	void set_radius(float rad) { radius = rad; }
	void set_axisAngle(float ax_ang) { axis_angle = ax_ang; }
	void set_scale(glm::vec3 scale_of) { thisScale = scale_of; }

	// 1 rotation per input sec
	void set_Sec_orbitANDrotate(float orbit, float rotate);
	void set_Theta_orbitANDrotate(system_clock::time_point lastTime);


	float return_radius() { return radius; }
	glm::vec4& return_sphereColor() { return sphereColor[0]; }
	glm::mat4& return_Model() { return ModelMat; }
	glm::vec3 return_planetPosition() { return planet_position; }
	glm::vec3 return_lookatPosition() { return planet_position; }
	glm::vec3 return_cameraPosition() { return camera_position; }
	glm::vec3 return_cameraVup() { return camera_vup; }

	// Color
	void init_Color(glm::vec4 PlanetCor[]);
	void set_Color(int colorIdx[], int numVertSphere);

	// Model
	void set_Model(glm::mat4 Model) { ModelMat = Model; }
	void transform_Model();

	// Camera
	void set_cameraPosition();
	void setBack_cameraPosition();
	void move_cameraPosition(float dir);
};


class Satellite : public Planet {

public:
	Satellite() {}
	Satellite(float rad, float ax_ang, glm::vec3 scale_of) {
		this->radius = rad;
		this->axis_angle = ax_ang;
		this->thisScale = scale_of;
	}

	// Satellite have to input its org_planet
	void transform_Model(Planet org_planet);
};
