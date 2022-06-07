#include "./includes/planet.h"

// Planet
void Planet::init_Color(glm::vec4 PlanetColor[]) {
	for (int i = 0; i < 6; i++) {
		vertColor[i] = PlanetColor[i];
	}
}

void Planet::set_Color(int colorIdx[], int numVertSphere) {

	for (int i = 0; i < numVertSphere; i++) {
		sphereColor[i] = vertColor[colorIdx[i]];
	}

}

void Planet::set_Sec_orbitANDrotate(float orbit, float rotate) {
	orbit_sec = orbit;
	rotate_sec = rotate;

	if (orbit_sec == 0) orbit_sec = DEFAULT_SEC;
}

void Planet::set_Theta_orbitANDrotate(system_clock::time_point lastTime) {

	// 1 rotate per sec
	system_clock::time_point curTime = system_clock::now();
	milliseconds elapsedTimeMSEC = duration_cast<milliseconds>(curTime - lastTime); // in millisecond
	orbit_theta = -(elapsedTimeMSEC.count() / 1000.0F) * ((float)M_PI * 2) / orbit_sec; // in <math.h>, M_PI_2 = pi/2
	rotate_theta = (elapsedTimeMSEC.count() / 1000.0F) * ((float)M_PI * 2) / rotate_sec;

}

void Planet::transform_Model() {

	float x = radius * cosf(orbit_theta);
	float z = radius * sinf(orbit_theta);

	planet_position = glm::vec3(x, 0.0F, z);

	ModelMat = glm::mat4(1.0F);
	ModelMat = glm::translate(ModelMat, glm::vec3(x, 0.0F, z));
	ModelMat = glm::rotate(ModelMat, axis_angle, glm::vec3(0.0F, 0.0F, 1.0F));
	ModelMat = glm::rotate(ModelMat, rotate_theta, glm::vec3(0.0F, 1.0F, 0.0F));
	ModelMat = glm::scale(ModelMat, thisScale);

}

void Planet::setBack_cameraPosition() {
	camera_theta = 0.0F;
}
 
void Planet::set_cameraPosition() {

	float x = planet_position.x + camera_radius * cosf(orbit_theta + camera_theta);
	float z = planet_position.z + camera_radius * sinf(orbit_theta + camera_theta);

	camera_position = glm::vec3(x , 0.0F, z );
	camera_vup = glm::vec3(0.0F, 1.0F, 0.0F);
}

void Planet::move_cameraPosition(float dir) {
	camera_theta += dir * ((float)M_PI / 180 * 0.25F);  // 0.25 degree
}

void Satellite::transform_Model(Planet org_planet) {

	glm::vec3 org_planet_position = org_planet.return_planetPosition();

	float x = org_planet_position.x + radius * cosf(orbit_theta);
	float z = org_planet_position.z + radius * sinf(orbit_theta);

	ModelMat = glm::mat4(1.0F);
	ModelMat = glm::translate(ModelMat, glm::vec3(x, 0.0F, z));
	ModelMat = glm::rotate(ModelMat, axis_angle, glm::vec3(0.0F, 0.0F, 1.0F));
	ModelMat = glm::rotate(ModelMat, rotate_theta, glm::vec3(0.0F, 1.0F, 0.0F));
	ModelMat = glm::scale(ModelMat, thisScale);

	//camera_position = glm::vec3((radius + 1.3F) * cosf(orbit_theta), 0.0F, (radius + 1.3F) * sinf(orbit_theta));
	//camera_vup = glm::vec3(0.0F, 1.0F, 0.0F);
}