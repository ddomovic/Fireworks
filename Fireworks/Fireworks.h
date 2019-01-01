#pragma once
#ifndef RG_LAB2_H_
#define RG_LAB2_H_

#include <GL/glut.h>

#define G 9.81

void display_f();
void reshape_f(int w, int h);
void mouse_f(int button, int state, int x, int y);
void keyboard_f(unsigned char theKey, int mouseX, int mouseY);
void create_particles(int n);
void draw_fireworks(GLfloat current_time);
void shape_particles(int n);
void draw_rocket(GLfloat current_time);

#endif
