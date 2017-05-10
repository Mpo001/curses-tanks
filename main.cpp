#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>
#include "Vec2D.hpp"

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

//const double PI = 3.141592653589793238463;

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



	// this timer updates with the the touch of the the key board not continous 
	ss = stringstream();
	ss << "WELCOME PLAYERS TO TANKS!!!";
		move(0, (COLS/2 - 23));
	addstr(ss.str().c_str());
	
	
	

	ss = stringstream();
	ss << " Score:  " << setfill('0') << setw(4) << score << " ";
	move(0, COLS - 19);
	addstr(ss.str().c_str());


}
//http://www.iforce2d.net/b2dtut/projected-trajectory

void force(double x, double y)
{
    x = Vec2D().getforceX() * 0.2;
    y = Vec2D().getforceY() * 0.2;
}

void Shoot(Ground & g, Player * players, int turn)
{
   if(players[turn].s == RIGHT)
       Vec2D().getforceX() &&  -(Vec2D().getforceX());
    
  
    double time_div = 15.0;
    double pnx, pny;
    double p0x = Vec2D().getp0();
    double p0y = g.ground.at(players[turn].col);
    p0y = LINES - p0y;
    
    for(int i = 1; i < 5000; i++)
    {
       // double angle = players[turn].angle / 180.0 * PI;
        
        pnx = (int)(p0x + Vec2D().getdi() * Vec2D().getforceX());
        pny = (int)(p0y + Vec2D().getdi() * Vec2D().getforceY() + ((Vec2D().getdi() * Vec2D().getdi() + Vec2D().getdi())) * -9.8 / time_div / 1.5);
        pny = (LINES - pny);
        
        if (pnx < 1 || pnx >= COLS - 2)
           break;
        if (pnx == p0y )
            //break;
        if (pny < 1)
        {
            MySleep(10);
            continue;
        }
        if (pny > g.ground.at((int)pnx))
            break;
        move((int)Vec2D().getpNy() - 1, (int)Vec2D().getpNx()+ 1);
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
			turn = turn - 1;
			break;
        

		default:
			show_char = true;
			break;
		}
		DrawScreen(g, players, turn);
		if (show_char)
        {
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
