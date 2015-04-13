//
//  Entity.h
//  RayTracing
//
//  Created by Zackary T Misso on 4/10/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Entity__
#define __RayTracing__Entity__

#include <stdio.h>
#include "Ray.h"
//#include "Vector3.h"
#include "Color.h"

class Entity{
private:
public:
    Entity();
    virtual Color getColor();
    virtual Vector3 getNormalAt(Vector3 point);
    virtual number findIntersection(Ray ray);
};

#endif /* defined(__RayTracing__Entity__) */
