#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#if defined(WIN32)
#include <Windows.h>
#include "curses.h"
#else
#include <unistd.h>
#include <curses.h>
#endif

using namespace std;

struct POS
{
	POS();
	int l;
	int c;
};

POS::POS()
{
	l = rand() % (LINES - 2) + 1;
	c = rand() % (COLS - 2) + 1;
}

struct Food
{
	Food();
	POS p;
	int v;
	void Render();
};

Food::Food()
{
	v = rand() % 5 + 5;
	p = POS();
}

void Food::Render()
{
	move(p.l, p.c);
	stringstream ss;
	ss << v;
	addstr(ss.str().c_str());
}



struct Worm
{
	Worm();
	vector<POS> segments;
	void Render();
	bool LandsOnMe;
	void initalize();
	bool move(int deltaT);
};

void Worm::initalize()
{
	POS p;
	p.l = LINES / 2;
	p.c = COLS / 2;
	segments.push_back(p);

	for (int i = 0; i < 6; i++)
	{
		p.l = segments.at(i).l;
		p.c = segments.at(i).c - 1;
		segments.push_back(p);
	}

}

Worm::Worm()
{
	initalize();
}

void Worm::Render()
{
	for (size_t i = 0; i < segments.size(); i++)
	{
		move(segments.at(i).c , segments.at(i).l);
		addch((i == 0) ? '@' : 'o');
	}
}

bool Worm:: move(int deltaT)
{
	bool rev = true;
	int dl = 0;
	int dc = 0;
	for (int i = segments.size() - 1; i > 0; i--)
	{
		segments[i] = segments[i - 1];
	}

		if (deltaT == '3')
		{
			dl--;
		}
		if (deltaT == '4')
		{
			dl++;
		}if (deltaT == '5')
		{
			dc--;
		}if (deltaT == '6')
		{
			dc++;
		}
		segments[0] = POS(segments[0].c + dc, segments[0].l + dl);

}


bool ProcessKeyboard(Food & f)
{
	bool rv = false;

	char c = getch();
	switch (c)
	{


	case 'F':
		f = Food();
		break;
	}
	return rv;
}

void DrawBorder(int score, time_t st)
{
	border(0, 0, 0, 0, 0, 0, 0, 0);
	stringstream ss;
	ss << " Score: " << setw(4) << score << " ";
	move(0, 2);
	addstr(ss.str().c_str());

	int dT = static_cast<int>(difftime(time(nullptr), st));
	int seconds = dT % 60;
	int minutes = dT / 60 % 60;
	int hours = dT / 3600 % 24;

	ss = stringstream();
	ss << " Time: " << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds << " ";
	move(0, COLS - 20);
	addstr(ss.str().c_str());
}

void Die()
{
	char die_chars[] = { '/', '-' , '\\', '|', 0 };

	while (getch() == ERR)
	{
		for (int i = 0; die_chars[i] != 0; i++)
		{
			for (int l = 1; l < LINES - 1; l++)
			{
				for (int c = 1; c < COLS - 1; c++)
				{
					move(l, c);
					addch(die_chars[i]);
				}
			}
			refresh();
			Sleep(200);
		}
	}
}

int main()
{
	srand((unsigned int)time(nullptr));

	time_t start_time;
	int score = 0;

	initscr();
	keypad(stdscr, 1);
	cbreak();
	noecho();
	nodelay(stdscr, 1);
	curs_set(0);

	start_time = time(nullptr);
	Food f;
	Worm w;

	while (true)
	{

		if (ProcessKeyboard(f))
		{
			break;
		}
		clear();
		DrawBorder(score, start_time);
		f.Render();
		w.Render();
		refresh();
	}
	Die();
	endwin();
}