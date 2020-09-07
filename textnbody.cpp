#include <iostream>
#include <Windows.h>
#include <cmath>
#include "textnbody.h"

using namespace std;

int main()
{
	int bodies;
	cout << "How many bodies do you want to simulate? ";
	cin >> bodies;

	nbody* nbodies;
	nbodies = new nbody[bodies];
	getNbodies(nbodies, bodies);

	clear();
	cout << "All bodies initialized." << endl;
	system("Pause");

	while (!(GetKeyState('P') & 0x8000))
	{
		clear();
		int start_time = GetTickCount();

		updateNbodies(nbodies, bodies);
		displayNbodies(nbodies, bodies);

		int time_left = 16 - (GetTickCount() - start_time);
		Sleep((time_left < 0) ? 0 : time_left);
	}

	return 0;
}

void getNbodies(nbody* nbodies, int body_count)
{
	for (int i = 0; i < body_count; i++)
	{
		nbody body;
		cout << "What is the symbol for this body? ";
		cin >> body.symbol;

		cout << "What is the mass of this body? ";
		cin >> body.mass;

		cout << "What is the x position of this body? ";
		cin >> body.x;

		cout << "What is the y position of this body? ";
		cin >> body.y;

		cout << "What is the x velocity of this body? ";
		cin >> body.x_vel;

		cout << "What is the y velocity of this body? ";
		cin >> body.y_vel;

		*(nbodies + i) = body;
		cout << endl;
	}
}

void updateNbodies(nbody* nbodies, int body_count) 
{
	for (int i = 0; i < body_count; i++)
	{
		nbody b1 = *(nbodies + i);
		double a_x = 0;
		double a_y = 0;
		for (int j = 0; j < body_count; j++)
		{
			if (j == i) continue;
			nbody b2 = *(nbodies + j);
			double r = sqrt(pow(b1.x - b2.x, 2) + pow(b1.y - b2.y, 2));
			a_x -= (b2.mass * (b1.x - b2.x)) / pow(r, 3);
			a_y -= (b2.mass * (b1.y - b2.y)) / pow(r, 3);
		}
		b1.x_vel += a_x * dt;
		b1.y_vel += a_y * dt;
		*(nbodies + i) = b1;
	}

	for (int i = 0; i < body_count; i++)
	{
		nbody b1 = *(nbodies + i);
		b1.x += b1.x_vel * dt;
		b1.y += b1.y_vel * dt;
		*(nbodies + i) = b1;
	}
}

//slower display method
/*void displayNbodies(nbody* nbodies, int body_count)
{
	char display[height][width + 1];

	for (int i = 0; i < height; i++)//y
	{
		for (int j = 0; j < width; j++)//x
		{
			display[i][j] = ' ';
		}
		display[i][width] = '\0';
	}

	for (int i = 0; i < body_count; i++)
	{
		nbody b = *(nbodies + i);
		int px = (int)round(b.x);
		int py = (int)round(b.y);
		if (px < width && px >= 0 && py < height && py >= 0)
			display[py][px] = b.symbol;
	}

	for (int i = 0; i < height; i++)
	{
		cout << display[i] << endl;
	}

}*/

void displayNbodies(nbody* nbodies, int body_count)
{
	for (int i = 0; i < body_count; i++)
	{
		nbody b = *(nbodies + i);
		int px = (int)round(b.x);
		int py = (int)round(b.y);
		if (px < width && px >= 0 && py < height && py >= 0)
		{
			COORD coord;
			coord.X = px;
			coord.Y = py;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			printf("%c", b.symbol);
		}
	}

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}