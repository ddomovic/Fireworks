#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <math.h>
#include <vector>
#ifdef _unix
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include <ctime>
#include <random>
#include "Particle.h"
#include "Fireworks.h"

GLuint window;
GLuint width = 1000, height = 700;
GLuint object;
GLfloat start_time;
GLfloat rot_f = 0;

bool normal_random = true;
int number_of_particles = 1000;

GLint key_x = 0;
GLint key_y = 0;
GLint key_z = -20;
GLint key_rot = 0;
GLint key_rot_x = 0;

std::vector<Particle*> particles;

void display_f() {

	glClearColor(0, 0, 0, 1);

	glLoadIdentity();
	glTranslatef(key_x, key_y, key_z);
	//glScalef(0.5, 0.5, 0.5);
	glRotatef(key_rot, 0, 1, 0);
	glRotatef(key_rot_x, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(4.0);
	GLfloat current_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	if (current_time - start_time < 1000) {
		draw_rocket((current_time - start_time) / 1000.0);
	}
	else if ((current_time - start_time < 3000) && (current_time - start_time >= 1000)) {
		draw_fireworks((current_time - start_time - 1000) / 1000.0);
	}
	glFlush();

	if (current_time - start_time >= 4000) {
		shape_particles(number_of_particles);
		start_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	}
}

void reshape_f(int w, int h) {

	width = w;
	height = h;

	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, width, 0, height, -1000, 1024);
	gluPerspective(45.0f, ((double)width / height), 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glColor3f(0.0f, 0.0f, 0.0f);

}

void mouse_f(int button, int state, int x, int y) {

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		reshape_f(width, height);
		glFlush();
	}
}

void keyboard_f(unsigned char theKey, int mouseX, int mouseY) {
	switch (theKey) {

	case 'w':
		key_y++;
		break;
	case 's':
		key_y--;
		break;
	case 'a':
		key_x--;
		break;
	case 'd':
		key_x++;
		break;
	case 'q':
		key_z++;
		break;
	case 'e':
		key_z--;
		break;
	case 'r':
		key_rot--;
		break;
	case 't':
		key_rot++;
		break;
	case 'f':
		key_rot_x--;
		break;
	case 'g':
		key_rot_x++;
		break;
	case 'p':
		exit(0);
		break;
	}
}

void draw_rocket(GLfloat current_time) {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0, 10.0 * current_time - 10.2, 0.0);
	glVertex3f(0.0, 10.0 * current_time - 9.8, 0.0);
	glEnd();
	glLineWidth(1.0f);
}

void draw_fireworks(GLfloat current_time) {

	glBegin(GL_POINTS);
	for (int i = 0; i < particles.size(); i++) {
		if (current_time > particles[i]->get_life_length()) {
			glColor4f(particles[i]->get_color().x, particles[i]->get_color().y, particles[i]->get_color().z, 0.0);
		}
		else {
			glColor4f(particles[i]->get_color().x, particles[i]->get_color().y, particles[i]->get_color().z, exp(-1 * current_time / particles[i]->get_life_length()));
			//glBlendFunc(GL_ONE, GL_ZERO);
		}
		glm::vec3 v = particles[i]->get_v0();
		GLfloat x = v.x * current_time;
		GLfloat y = v.y * current_time - 0.5 * G * pow(current_time, 2);
		GLfloat z = v.z * current_time;

		glVertex3f(x, y, z);
	}
	glEnd();
}

void create_particles(int n) {

	for (int i = 0; i < n; i++) {
		particles.push_back(new Particle());
	}
}

void shape_particles(int n) {

	srand(time(NULL));
	std::default_random_engine generator(std::random_device{}());
	std::normal_distribution<GLfloat> distribution(0.0, 1.0);
	distribution.reset();

	int n1 = n / 3;
	int n2 = n1 + n / 3;

	glm::vec3 col1((GLfloat)(rand()) / ((GLfloat)(RAND_MAX)), (GLfloat)(rand()) / ((GLfloat)(RAND_MAX)), (GLfloat)(rand()) / ((GLfloat)(RAND_MAX)));
	glm::vec3 col2((GLfloat)(rand()) / ((GLfloat)(RAND_MAX)), (GLfloat)(rand()) / ((GLfloat)(RAND_MAX)), (GLfloat)(rand()) / ((GLfloat)(RAND_MAX)));
	glm::vec3 col3((GLfloat)(rand()) / ((GLfloat)(RAND_MAX)), (GLfloat)(rand()) / ((GLfloat)(RAND_MAX)), (GLfloat)(rand()) / ((GLfloat)(RAND_MAX)));

	for (int i = 0; i < n; i++) {

		glm::vec4 col;
		if (i < n1) {
			col = glm::vec4(col1.x, col1.y, col1.z, 1.0);
		}
		else if (i < n2) {
			col = glm::vec4(col2.x, col2.y, col2.z, 1.0);
		}
		else {
			col = glm::vec4(col3.x, col3.y, col3.z, 1.0);
		}

		GLfloat vx;
		GLfloat vy;
		GLfloat vz;

		if (!normal_random) {
			vx = -4 + (GLfloat)(rand()) / ((GLfloat)(RAND_MAX / 8.0));
			vy = 9 + (GLfloat)(rand()) / ((GLfloat)(RAND_MAX / 2.0));
			vz = -2.5 + (GLfloat)(rand()) / ((GLfloat)(RAND_MAX / 5.0));
		}
		else {
			vx = distribution(generator) * 2;
			vy = distribution(generator) * 1 + 10;
			vz = distribution(generator) * 2.5;
		}
		glm::vec3 speed(vx, vy, vz);
		particles[i]->set_v0(speed);
		particles[i]->set_life_length(1.5 + (GLfloat)(rand()) / ((GLfloat)RAND_MAX / 0.5));
		particles[i]->set_color(col);
	}
}

int main(int argc, char *argv[]) {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);

	create_particles(number_of_particles);
	shape_particles(number_of_particles);

	window = glutCreateWindow("Fireworks");
	glutReshapeFunc(reshape_f);
	glEnable(GL_BLEND);
	glutFullScreen();
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	start_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	glutDisplayFunc(display_f);
	glutIdleFunc(display_f);
	glutMouseFunc(mouse_f);
	glutKeyboardFunc(keyboard_f);
	glutMainLoop();

	return 0;
}
