//
//  Vect2D.cpp
//  curses-tanks-m
//
//  Created by Mike Omohundro on 5/2/17.
//  Copyright © 2017 Carthage College. All rights reserved.
//

#include "Vec2D.hpp"

Vec2D :: Vec2D(double line, double column)
{
    y = line;
    x = column;
}

Vec2D::Vec2D(double line, double column, double gravity)
{
    
}

void Vec2D::setX(double X)
{
    x = X;
}

double Vec2D::getX()
{
    return x;
}




