#pragma once

struct nbody
{
	char symbol = 'O';
	double mass = 0;
	double x = 0;
	double y = 0;
	double x_vel = 0;
	double y_vel = 0;
};

void getNbodies(nbody* nbodies, int body_count);
void updateNbodies(nbody* nbodies, int body_count);
void displayNbodies(nbody* nbodies, int body_count);
void wipescreen();
void clear();

const double dt = 0.5;
const int height = 50, width = 150;
char display[height][width + 1];
