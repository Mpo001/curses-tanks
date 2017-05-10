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
    void setp0(int); //pos x
    int getp0();
    
    void setforceX(double);
    double getforceX();
    
    void setforceY(double);//force
    double getforceY();
    
    void setpNx(double);
    double  getpNx();
    
    void setpNy(double);
    double getpNy();
    
    void setgravity(double);
    double getGravity();
    
    void setdi(double);
    double getdi();
    
private:
    int cols, column;
    double forx, fx;
    double fory, fy;
    double X , x, y , Y;
    double grav;
    double DI;
};


