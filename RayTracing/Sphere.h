//
//  Sphere.h
//  RayTracing
//
//  Created by Zackary T Misso on 4/10/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Sphere__
#define __RayTracing__Sphere__

#include <stdio.h>
#include "Vector3.h"
#include "Color.h"
#include "Entity.h"

class Sphere : public Entity{
private:
    Vector3 position;
    Color color;
    number radius;
public:
    Sphere();
    Sphere(Vector3 pos,Color col,number r);
    Vector3 getPosition();
    virtual Color getColor();
    number getRadius();
    virtual number findIntersection(Ray ray);
    virtual Vector3 getNormalAt(Vector3 point);
};

#endif /* defined(__RayTracing__Sphere__) */
