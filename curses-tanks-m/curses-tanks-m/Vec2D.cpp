//
//  Vect2D.cpp
//  curses-tanks-m
//
//  Created by Mike Omohundro on 5/2/17.
//  Copyright © 2017 Carthage College. All rights reserved.
//

#include "Vec2D.hpp"
#include <curses.h>
#include <cstdlib>
#include "ground.hpp"
#include "player.hpp"
#include <cmath>

Vec2D :: Vec2D()
{
    column = Player().col;
    fory = cos(Player().angle * Player().power * 0.2);
    forx = sin(Player().angle * Player().power * 0.2);
    X = x;
    Y = y;
    grav = -0.98;
}

void Vec2D :: setp0(int cols)
{
    column = cols;
}

int Vec2D:: getp0()
{
    return cols;
}

void Vec2D :: setforceY(double fy)
{
    fory = fy;
    
}
double Vec2D :: getforceY()
{
    return fy;
}

void Vec2D :: setforceX(double fx)
{
    forx = fx;
}

double Vec2D :: getforceX()
{
    return fx;
}



void Vec2D:: setpNx(double x)
{
    
    int i;
    const int  time_divder = 15.0;
    const int di = i / time_divder;
    x = ((Player().col) + di * forx);
    x = X;
 
}
double Vec2D :: getpNx()
{
    return X;
}
void Vec2D:: setpNy(double y)
{
    int i;
    const int time_divder = 15.0;
    const int di = i / time_divder;
    y = ( Player().col + di * fory + (di * di + di)* -9.8 / time_divder / 1.5);
    y = Y;
}
double Vec2D :: getpNy()
{
    return Y;
}

void Vec2D:: setgravity(double ity)
{
    ity = grav;
}

double Vec2D:: getGravity()
{
    return grav;

}


