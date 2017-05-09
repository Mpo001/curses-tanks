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
    Vec2D(double line, double column);
    Vec2D(double line, double column, double gravity);
    void setX(double x);
    double getX();
    
private:
    double x;
    double y;
    
};
