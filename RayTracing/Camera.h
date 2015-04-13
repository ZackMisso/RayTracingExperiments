//
//  Camera.h
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Camera__
#define __RayTracing__Camera__

#include <iostream>
#include "Vector3.h"

class Camera{
private:
    Vector3 cameraPos;
    Vector3 cameraDir;
    Vector3 cameraRight;
    Vector3 cameraDown;
public:
    Camera();
    Camera(Vector3 pos,Vector3 dir,Vector3 right,Vector3 down);
    Vector3 getCameraPos(){return cameraPos;}
    Vector3 getCameraDir(){return cameraDir;}
    Vector3 getCameraRight(){return cameraRight;}
    Vector3 getCameraDown(){return cameraDown;}
};

#endif /* defined(__RayTracing__Camera__) */
