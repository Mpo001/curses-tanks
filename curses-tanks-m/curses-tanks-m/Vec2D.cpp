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
    const double PI = 3.141592653589793238463;
    double angle = Player().angle / 180 * PI * 0.2;
    forx = cos(angle)* Player().power * 0.2;
    fory = sin(angle) * Player().power * 0.2;
    X = x;
    Y = y;
    grav = -0.98;
    
    double i;
    double time_div = 15.0;
    DI = i / time_div;
}

void Vec2D :: setp0(int col)
{
    column = col;
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
    
//    int i;
//    const int;
//    const int di = i / double time_divder;
//    x = ((Player().col) + DI * forx);
    x = X;
 
}
double Vec2D :: getpNx()
{
    return X;
}
void Vec2D:: setpNy(double y)
{
    double time_div = 15.0;
    y = ( Player().col + DI * fory + (DI * DI + DI)* -9.8 / time_div / 1.5);
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

void Vec2D:: setdi(double d)
{
    DI = d;
}
double Vec2D:: getdi()
{
    return DI;
}


