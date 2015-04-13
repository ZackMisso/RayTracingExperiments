//
//  Vector3.h
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Vector3__
#define __RayTracing__Vector3__

#include <iostream>
#include <math.h>
typedef double number;

class Vector3{
private:
    number x;
    number y;
    number z;
public:
    Vector3(number x,number y,number z);
    Vector3 normalize();
    Vector3 negative();
    Vector3 cross(Vector3 b);
    Vector3 add(Vector3 b);
    Vector3 mult(number scalar);
    number magnitude();
    number dot(Vector3 b);
    number getX(){return x;}
    number getY(){return y;}
    number getZ(){return z;}
};

#endif /* defined(__RayTracing__Vector3__) */