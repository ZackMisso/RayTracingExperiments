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
//typedef float number;

class Plane : public Entity{
    Vector3 normal;
    Color color;
    number distance;
public:
    Plane();
    Plane(Vector3 norm,Color col,number dist);
    Vector3 getPlaneNormal();
    virtual Vector3 getNormalAt(Vector3 point);
    virtual Color getColor();
    number getDistance();
    virtual number findIntersection(Ray ray);
};

#endif /* defined(__RayTracing__Plane__) */
