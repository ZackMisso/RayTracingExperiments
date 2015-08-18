//
//  Plane.h
//  RayTracing
//
//  Created by Zackary T Misso on 4/10/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Plane__
#define __RayTracing__Plane__

#include <stdio.h>
#include "Entity.h"

class Plane : public Entity{
    Vector3 normal;
    Color color;
    number distance; // what is distance? Why am I using it???
public:
    Plane();
    Plane(Vector3 norm,Color col,number dist);
    Vector3 getPlaneNormal();
    Vector3 getNormalAt(Vector3 point);
    Color getColor();
    number getDistance();
    number findIntersection(Ray *ray);
};

#endif /* defined(__RayTracing__Plane__) */
