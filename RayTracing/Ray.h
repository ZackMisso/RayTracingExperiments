//
//  Ray.h
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Ray__
#define __RayTracing__Ray__

#include <iostream>
#include "Vector3.h"

class Ray{
private:
    Vector3 origin;
    Vector3 direction;
public:
    Ray();
    Ray(Vector3 origin,Vector3 direction);
    Vector3 getOrigin(){return origin;}
    Vector3 getDirection(){return direction;}
};

#endif /* defined(__RayTracing__Ray__) */
