#include "pch.h"
#include <cmath>
#include "Particle.h"

Particle::Particle() {
	this->color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->birth_time_ = 0.0;
	this->starting_position_ = glm::vec3(0, 0, 0);
	this->direction_ = glm::vec3(1, 1, 1);
	this->v0_ = glm::vec3(10, 10, 10);
}

Particle::Particle(glm::vec4 color, GLfloat birth_time, GLfloat life_length, glm::vec3 starting_position, glm::vec3 direction, glm::vec3 v0) {
	this->color_ = color;
	this->birth_time_ = birth_time;
	this->life_length_ = life_length;
	this->starting_position_ = starting_position;
	this->direction_ = direction;
	this->v0_ = v0;
}

glm::vec4 Particle::get_color() {
	return this->color_;
}

GLfloat Particle::get_birth_time() {
	return this->birth_time_;
}

GLfloat Particle::get_life_length() {
	return this->life_length_;
}

glm::vec3 Particle::get_starting_position() {
	return this->starting_position_;
}

glm::vec3 Particle::get_direction() {
	return this->direction_;
}

glm::vec3 Particle::get_v0() {
	return this->v0_;
}

void Particle::set_color(glm::vec4 color) {
	this->color_ = color;
}

void Particle::set_birth_time(GLfloat birth_time) {
	this->birth_time_ = birth_time;
}

void Particle::set_life_length(GLfloat life_length) {
	this->life_length_ = life_length;
}

void Particle::set_starting_position(glm::vec3 starting_position) {
	this->starting_position_ = starting_position;
}

void Particle::set_direction(glm::vec3 direction) {
	this->direction_ = direction;
}

void Particle::set_v0(glm::vec3 v0) {
	this->v0_ = v0;
}
