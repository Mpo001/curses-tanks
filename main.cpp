#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>


#if defined(_WIN32)
#include <Windows.h>
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#include <unistd.h>
#endif

#include "ground.hpp"
#include "player.hpp"

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

void MySleep(int milliseconds)
{
#if defined(WIN32)
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}
void DrawScreen(Ground & g, Player * players, int turn)
{
	erase();
	box(stdscr, 0, 0);
	g.Draw();
	players[0].Draw(g);
	players[1].Draw(g);
	players[0].DrawSettings(turn);
	players[1].DrawSettings(turn);
	refresh();
}

void DrawBorder(int score, time_t st)
{
	border(0, 0, 0, 0, 0, 0, 0, 0);
	stringstream ss;
	ss << " Score:  " << setfill('0') << setw(4) << score << " ";
	move(0, 2);
	addstr(ss.str().c_str());

	int dT = static_cast<int>(difftime(time(nullptr), st));
	int seconds = dT % 60;
	int minutes = dT / 60 % 60;
	int hours = dT / 3600 % 24;

	// this timer updates with the the touch of the the key board not continous 
	ss = stringstream();
	ss << "WELCOME PLAYERS TO TANKS!!!";
	//ss << " Time: " << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds << " ";
	move(0, (COLS/2 - 23));
	addstr(ss.str().c_str());
	
	
	

	ss = stringstream();
	ss << " Score:  " << setfill('0') << setw(4) << score << " ";
	move(0, COLS - 19);
	addstr(ss.str().c_str());


}
//http://www.iforce2d.net/b2dtut/projected-trajectory

void Shoot(Ground & g, Player * players, int turn)
{
	double angle = players[turn].angle / 180.0 * PI;
	double y_component = sin(angle) * players[turn].power * 0.2;
	double x_component = cos(angle) * players[turn].power * 0.2;
    
   // Vec2D force(sin(angle) * players[turn].power * 0.2, cos(angle) * players[turn].power * 0.2);

	double pNx;
	double pNy;
    
    //Vect2D(pNx, pNy);
    
	double time_divisor = 15.0;

	if (players[turn].s == RIGHT)
		x_component = -x_component;

	double p0x = players[turn].col;
	double p0y = g.ground.at(players[turn].col);
	// higher ground numbers are lower altitudes (0 is first line, etc).
	p0y = LINES - p0y;
	for (int i = 1; i < 5000; i++)
	{
		double di = i / time_divisor;

		pNx = (int)(p0x + di * x_component);
		pNy = p0y + di * y_component + (di * di + di) * -9.8 / time_divisor / 1.5;
		pNy = (int)(LINES - pNy);
		if (pNx < 1 || pNx >= COLS - 2)
			break;
		if (pNy < 1) {
			MySleep(50);
			continue;
		}
		//	if (pNy >= LINES - 2)
		//		break;
		if (pNy > g.ground.at((int)pNx))
			break;

		move((int)pNy - 1, (int)pNx + 1);
		addch('*');
		refresh();
		MySleep(50);
	}
}

int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	time_t start_time;
	int score = 0;
	Ground g;
	Player players[2];
	bool keep_going = true;

	initscr();
	noecho();
	keypad(stdscr, 1);

	g.InitializeGround();
	players[0].Initialize(rand() % (COLS / 4), LEFT);
	players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);
	start_time = time(nullptr);
	DrawScreen(g, players, turn);
	
	
	while (keep_going)
	{
		DrawBorder(score, start_time);

		bool show_char = false;
		int c = getch();
		switch (c)
		{
		case 27:
			keep_going = false;
			break;

		case 's':
			players[turn].PowerDown();
			break;

		case 'w':
			players[turn].PowerUp();
			break;

		case 'a':
			players[turn].AngleUp();
			break;

		case 'd':
			players[turn].AngleDown();
			break;

		case 10:
		case KEY_ENTER:
#if defined(WIN32)
		case PADENTER:
#endif
			Shoot(g, players, turn);
			turn = 1 - turn;
			break;

		default:
			show_char = true;
			break;
		}
		DrawScreen(g, players, turn);
		if (show_char) {
			move(0, 1);
			stringstream ss;
			ss << setw(4) << c << " ";
			addstr(ss.str().c_str());
			refresh();
		}
		
	}
	
	erase();
	addstr("Hit any key to exit");
	refresh();
	getch();
	echo();
	endwin();
	return 0;
}
