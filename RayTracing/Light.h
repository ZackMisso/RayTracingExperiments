//
//  Light.h
//  RayTracing
//
//  Created by Zackary T Misso on 3/26/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Light__
#define __RayTracing__Light__

#include "Vector3.h"
#include "Color.h"
#include "Source.h"

class Light : public Source{
private:
    Vector3 position;
    Color color;
public:
    Light();
    Light(Vector3 pos,Color col);
    virtual Vector3 getLightPosition();
    virtual Color getColor();
};

#endif /* defined(__RayTracing__Light__) */
