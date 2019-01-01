#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glut.h>

class Particle {
private:
	glm::vec4 color_;
	GLfloat birth_time_;
	GLfloat life_length_;
	glm::vec3 starting_position_;
	glm::vec3 direction_;
	glm::vec3 v0_;
public:
	Particle();
	Particle(glm::vec4 color, GLfloat birth_time, GLfloat life_length, glm::vec3 starting_position, glm::vec3 direction, glm::vec3 v0);
	glm::vec4 get_color();
	GLfloat get_birth_time();
	GLfloat get_life_length();
	glm::vec3 get_starting_position();
	glm::vec3 get_direction();
	glm::vec3 get_v0();
	void set_color(glm::vec4 color);
	void set_birth_time(GLfloat birth_time);
	void set_life_length(GLfloat life_length);
	void set_starting_position(glm::vec3 starting_position);
	void set_direction(glm::vec3 direction);
	void set_v0(glm::vec3 v0);
};
