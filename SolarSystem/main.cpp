#include "planet.h"	
#include "planet_info.h"
#include "makeSphere.h"
#include "camera.h"
#include "prcsLight.h"
#include "textureMapping.h"
#include "./common.c"

using namespace Sphere;
using namespace Camera;
using namespace LightSource;
using namespace texture;

const unsigned int WIN_W = 500; // window size in pixels, (Width, Height)
const unsigned int WIN_H = 500;
const unsigned int WIN_X = 100; // window position in pixels, (X, Y)
const unsigned int WIN_Y = 100;

const char* vertFileName = "planet.vert";
const char* fragFileName = "planet.frag";


GLuint vert = 0; // vertex shader ID number
GLuint frag = 0; // fragment shader ID number
GLuint prog = 0; // shader program ID number


void initFunc(void) {
	const char* vertSource = loadFile(vertFileName);
	const char* fragSource = loadFile(fragFileName);
	char buf[1024]; // mesg buffer
	GLint status; // for glGetShaderiv()
	// vert: vertex shader
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertSource, nullptr);
	glCompileShader(vert); // compile to get .OBJ
	glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
	printf("vert compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(vert, sizeof(buf), nullptr, buf);
	printf("vert log = [%s]\n", buf);
	// frag: fragment shader
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragSource, nullptr);
	glCompileShader(frag); // compile to get .OBJ
	glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
	printf("frag compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(frag, sizeof(buf), nullptr, buf);
	printf("frag log = [%s]\n", buf);

	// prog: program
	prog = glCreateProgram();
	
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);

	glLinkProgram(prog); // link to get .EXE
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("prog link status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), nullptr, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("prog validate status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), nullptr, buf);
	printf("validate log = [%s]\n", buf);
	fflush(stdout);

	// execute it!
	glUseProgram(prog);
	

	// done
	free((void*)vertSource);
	free((void*)fragSource);

}


// Declare planet as global 
Planet sun(sun_radius, sun_axis, sun_scale);
Planet mercury(mercury_radius, mercury_axis, mercury_scale);
Planet venus(venus_radius, venus_axis, venus_scale);
Planet earth(earth_radius, earth_axis, earth_scale);
Planet mars(mars_radius, mars_axis, mars_scale);
Satellite moon(moon_radius, moon_axis, moon_scale);

Planet jupiter(jupiter_radius, jupiter_axix, jupiter_scale);


system_clock::time_point lastTime = system_clock::now();


void init_planet() {

	Sphere::generateSphere(4);

	// ** needed before texture mapping
	/*sun.init_Color(SunColor);
	earth.init_Color(EarthColor);
	moon.init_Color(MoonColor);
	mars.init_Color(MarsColor);
	jupiter.init_Color(JupiterColor);

	sun.set_Color(Sphere::colorIdx, Sphere::numVertSphere);
	earth.set_Color(Sphere::colorIdx, Sphere::numVertSphere);
	moon.set_Color(Sphere::colorIdx, Sphere::numVertSphere);
	mars.set_Color(Sphere::colorIdx, Sphere::numVertSphere);
	jupiter.set_Color(Sphere::colorIdx, Sphere::numVertSphere);*/


	// set orbit 
	// Earth = 1.0000 = 30
	float earth_orbit = 30;
	// mercury = 0.2409 = 30 * 0.2409
	// venus = 0.6102 = 30 * 0.6102
	// mars = 1.8809 = 30 * 1.8809
	// jupiter = 11.862 = 30 * 11.862

	sun.set_Sec_orbitANDrotate(0, 20);
	mercury.set_Sec_orbitANDrotate(30 * 0.2409,2);
	venus.set_Sec_orbitANDrotate(30 * 0.6102, 5);
	earth.set_Sec_orbitANDrotate(30, 5);
	moon.set_Sec_orbitANDrotate(5, 1);
	mars.set_Sec_orbitANDrotate(30 * 1.8809, 5);
	jupiter.set_Sec_orbitANDrotate(30 * 11.862, 15);
}

void updateFunc(void) {
	
	// Planet transform
	sun.set_Theta_orbitANDrotate(lastTime);
	sun.transform_Model();
	sun.set_cameraPosition();

	mercury.set_Theta_orbitANDrotate(lastTime);
	mercury.transform_Model();
	mercury.set_cameraPosition();

	venus.set_Theta_orbitANDrotate(lastTime);
	venus.transform_Model();
	venus.set_cameraPosition();

	earth.set_Theta_orbitANDrotate(lastTime);
	earth.transform_Model();
	earth.set_cameraPosition();

	moon.set_Theta_orbitANDrotate(lastTime);
	moon.transform_Model(earth); 

	mars.set_Theta_orbitANDrotate(lastTime);
	mars.transform_Model();
	mars.set_cameraPosition();

	jupiter.set_Theta_orbitANDrotate(lastTime);
	jupiter.transform_Model();
	jupiter.set_cameraPosition();

	if (Camera::now == CAMERA_SUN) {
		sun.move_cameraPosition(Camera::Camera_status);

		Camera::target_now = Camera::target_org;
		Camera::camera_now = Camera::camera_org;
		Camera::vup_now = Camera::vup_org;
	}
	else if (Camera::now == CAMERA_MERCURY) {
		mercury.move_cameraPosition(Camera::Camera_status);

		Camera::target_now = mercury.return_lookatPosition();
		Camera::camera_now = mercury.return_cameraPosition();
		Camera::vup_now = mercury.return_cameraVup();
	}
	else if (Camera::now == CAMERA_VENUS) {
		venus.move_cameraPosition(Camera::Camera_status);

		Camera::target_now = venus.return_lookatPosition();
		Camera::camera_now = venus.return_cameraPosition();
		Camera::vup_now = venus.return_cameraVup();
	}
	else if (Camera::now == CAMERA_EARTH) {
		earth.move_cameraPosition(Camera::Camera_status);

		Camera::target_now = earth.return_lookatPosition();
		Camera::camera_now = earth.return_cameraPosition();
		Camera::vup_now = earth.return_cameraVup();
	}
	else if (Camera::now == CAMERA_MARS) {
		mars.move_cameraPosition(Camera::Camera_status);

		Camera::target_now = mars.return_lookatPosition();
		Camera::camera_now = mars.return_cameraPosition();
		Camera::vup_now = mars.return_cameraVup();
	}
	else if (Camera::now == CAMERA_JUPITER) {
		jupiter.move_cameraPosition(Camera::Camera_status);

		Camera::target_now = jupiter.return_lookatPosition();
		Camera::camera_now = jupiter.return_cameraPosition();
		Camera::vup_now = jupiter.return_cameraVup();
	}
	else if (Camera::now == CAMERA_UP_VIEW) {
		Camera::camera_now = glm::vec3(0.0F, 10.0F, 0.0F);
		Camera::target_now = glm::vec3(0.0F, 0.0F, 0.0F);
		Camera::vup_now = glm::vec3(0.0F, 0.0F, -1.0F);
		Camera::fovy = ((GLfloat)M_PI / 180.0F) * 60.0F;
	}

	Camera::matView = glm::lookAtRH(
		Camera::camera_now,
		Camera::target_now,
		Camera::vup_now
	);

	Camera::minimatView = glm::lookAtRH(
		glm::vec3(0.0F, 9.0F, 0.0F),
		glm::vec3(0.0F, 0.0F, 0.0F),
		glm::vec3(0.0F, 0.0F, -1.0F)
	);

	// projection matrix
	const GLfloat aspect = (GLfloat)WIN_W / (GLfloat)WIN_H;
	Camera::matProj = glm::perspectiveRH(Camera::fovy, aspect, +0.1F, +20.0F);
	Camera::minimatProj = glm::perspectiveRH(((GLfloat)M_PI / 180.0F) * 60.0F, aspect, +1.0F, +20.0F);

}


void Make_miniMap(GLint map_x, GLint map_y, GLsizei map_w, GLsizei map_h,
	int win_w, int win_h) {

	glViewport(map_x, map_y, map_w, map_h);
	glEnable(GL_SCISSOR_TEST);
	glScissor(map_x, map_y, map_w, map_h);
	glClearColor(0.4F, 0.4F, 0.4F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScissor(0, 0, win_w, win_h);
	glDisable(GL_SCISSOR_TEST);
}

void drawFunc(GLFWwindow* window) {
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0F, 1.0F);
	glClearDepthf(1.0F);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glClearColor(0.2F, 0.2F, 0.2F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set size miniMap
	int win_w, win_h;
	glfwGetWindowSize(window, &win_w, &win_h);
	GLint map_x = (GLint)(win_w * 0.70F);
	GLint map_y = (GLint)(win_h * 0.05F);
	GLsizei map_w = (GLsizei)(win_w * 0.25F);
	GLsizei map_h = (GLsizei)(win_h * 0.25F);


	// matrix settings
	GLuint locPos = glGetAttribLocation(prog, "aPos");
	GLuint locNorm = glGetAttribLocation(prog, "aNorm");
	GLuint locColor = glGetAttribLocation(prog, "aColor");
	GLuint locModel = glGetUniformLocation(prog, "uModel");
	GLuint locView = glGetUniformLocation(prog, "uView");
	GLuint locProj = glGetUniformLocation(prog, "uProj");
	GLuint locIs_lightSource = glGetUniformLocation(prog, "Is_lightSource");

	glEnableVertexAttribArray(locPos);
	glEnableVertexAttribArray(locNorm);
	glEnableVertexAttribArray(locColor);

	// set Light and Material
	LightSource::setLnM(prog);

	// Draw window
	glViewport(0, 0, win_w, win_h);

	glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(Camera::matView));
	glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(Camera::matProj));

	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(Sphere::vertSphere[0]));
	glVertexAttribPointer(locNorm, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(Sphere::normSphere[0]));
	
	// Draw Sun
	glUniform1i(locIs_lightSource, 1);
	
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(sun.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(sun.return_Model()));
	texture::usePlanetImage(SUN);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere); 


	// Draw Planet
	glUniform1i(locIs_lightSource, 0);
	
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(mercury.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mercury.return_Model()));
	texture::usePlanetImage(MERCURY);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(venus.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(venus.return_Model()));
	texture::usePlanetImage(VENUS);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);


	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(earth.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(earth.return_Model()));
	texture::usePlanetImage(EARTH);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(moon.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(moon.return_Model()));
	texture::usePlanetImage(MOON);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(mars.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mars.return_Model()));
	texture::usePlanetImage(MARS);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(jupiter.return_sphereColor()));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(jupiter.return_Model()));
	texture::usePlanetImage(JUPITER);
	glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

	
	// Draw minimap
	if (now != CAMERA_UP_VIEW) {
		Make_miniMap(map_x, map_y, map_w, map_h, win_w, win_h);
		glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(Camera::minimatView));
		glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(Camera::minimatProj));


		// Not to be affected by the light
		// Pretending to be a light source
		glUniform1i(locIs_lightSource, 1);

		// Draw Sun
		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(sun.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(sun.return_Model()));
		texture::usePlanetImage(SUN);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);


		// Draw Planet
		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(mercury.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mercury.return_Model()));
		texture::usePlanetImage(MERCURY);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(venus.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(venus.return_Model()));
		texture::usePlanetImage(VENUS);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(earth.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(earth.return_Model()));
		texture::usePlanetImage(EARTH);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);
		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(moon.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(moon.return_Model()));
		texture::usePlanetImage(MOON);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(mars.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mars.return_Model()));
		texture::usePlanetImage(MARS);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

		glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(jupiter.return_sphereColor()));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(jupiter.return_Model()));
		texture::usePlanetImage(JUPITER);
		glDrawArrays(GL_TRIANGLES, 0, Sphere::numVertSphere);

	}

	// done
	glFinish();
}

void refreshFunc(GLFWwindow* window) {
	// refresh
	drawFunc(window);
	// GLFW action
	glfwSwapBuffers(window);
}


void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	case GLFW_KEY_R:
		if (action == GLFW_PRESS) {
			lastTime = system_clock::now();
			Camera::fovy = ((GLfloat)M_PI / 180.0F) * 60.0F; // 60 degree
		}
		break;
	case GLFW_KEY_J:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			if (Camera::fovy < ((GLfloat)M_PI / 180.0F) * 90.0F) Camera::fovy += ((GLfloat)M_PI / 180.0F) * 1.0F;
		break;
	case GLFW_KEY_K:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			if (Camera::fovy > ((GLfloat)M_PI / 180.0F) * 0.0F) Camera::fovy -= ((GLfloat)M_PI / 180.0F) * 1.0F;
		break;
	case GLFW_KEY_9: Camera::now = CAMERA_UP_VIEW; break;
	case GLFW_KEY_0: Camera::now = CAMERA_SUN; sun.setBack_cameraPosition();  Camera::fovy = Camera::fovy_org; break;
	case GLFW_KEY_1: Camera::now = CAMERA_MERCURY; mercury.setBack_cameraPosition();  Camera::fovy = Camera::fovy_org; break;
	case GLFW_KEY_2: Camera::now = CAMERA_VENUS; venus.setBack_cameraPosition();  Camera::fovy = Camera::fovy_org; break;
	case GLFW_KEY_3: Camera::now = CAMERA_EARTH; earth.setBack_cameraPosition();  Camera::fovy = Camera::fovy_org;break;
	case GLFW_KEY_4: Camera::now = CAMERA_MARS; mars.setBack_cameraPosition(); Camera::fovy = Camera::fovy_org; break;
	case GLFW_KEY_5: Camera::now = CAMERA_JUPITER; jupiter.setBack_cameraPosition(); Camera::fovy = Camera::fovy_org; break;

	case GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			Camera_status = CAMERA_RIGHT;
		if (action == GLFW_RELEASE)
			Camera_status = CAMERA_PAUSE;
		break;
	case GLFW_KEY_LEFT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			Camera_status = CAMERA_LEFT;
		if (action == GLFW_RELEASE)
			Camera_status = CAMERA_PAUSE;
		break;
	default:
		break;

	}
}



int main(int argc, char* argv[]) {
	const char* basename = getBaseName(argv[0]);

	if (argc > 1) {
		levelSphere = strtol(argv[1], nullptr, 10);
	}

	
	// start GLFW & GLEW
	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, basename, nullptr, nullptr);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);
	glewInit();
	// prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.2F, 0.2F, 0.2F, 1.0F);
	
	// Make Planet
	init_planet();
	texture::CreateTexture();

	// main loop
	initFunc();
	while (!glfwWindowShouldClose(window)) {
		// animation loop
		updateFunc();
		drawFunc(window);
		// GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// done
	glfwTerminate();
	return 0;
}