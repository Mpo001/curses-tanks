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



void Vec2D :: p0(double c)
{
    c = Player().col;
}
//void Vec2D :: p0y(double line)
//{
//   line = Player().col;
//}

void Vec2D :: forceX(double forx)
{
    forx = sin(Player().angle * Player().power * 0.2);
}
void Vec2D :: forceY(double fory)
{
  fory = cos(Player().angle * Player().power * 0.2);
}

void Vec2D :: gravity( double a, double b)
{
    a = 0;
    b = rand();
    if( b < 1.1 || b > -0.98)
        b = rand();
}

void Vec2D:: pNx(double X)
{
    p0(c);
    forceX(x);
    
    
    if(Player().s == RIGHT)
       p0((-(Player().col)));
    int i;
    double  time_divder = 15.0;
    double di = i / time_divder;
        
   X = ((int)(c) + di * x);
}

void Vec2D:: pNy(double Y)
{
    
    p0(c);
    forceY(y);
    int i;
    double  time_divder = 15.0;
    double di = i / time_divder;
    Y = ( c + di * y + (di * di + di)* -9.8 / time_divder / 1.5);
    

}


//void Vec2D::setX(double X)
//{
//    x = X;
//}
//
//double Vec2D::getX()
//{
//    return x;
}




