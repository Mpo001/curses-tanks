//
//  Vect2D.hpp
//  curses-tanks-m
//
//  Created by Mike Omohundro on 5/2/17.
//  Copyright © 2017 Carthage College. All rights reserved.
//

#ifndef Vec2D_hpp
#define Vec2D_hpp

#include <stdio.h>

#endif /* Vec2D_hpp */


class Vec2D
{
public:
    Vec2D();
    void p0(double l); //pos x
    void p0y(double c); // pos y
    void forceX(double x);
    void forceY(double y);//force
    void gravity(double a, double b); // grav
    //void setX(double x);
    //double getX();
    void pNx(double X);
    void pNy(double Y);
    
private:
    double l;
    double c;
    double a;
    double b;
    double x;
    double y;
};
