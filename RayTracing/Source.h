//
//  Source.h
//  RayTracing
//
//  Created by Zackary T Misso on 4/11/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Source__
#define __RayTracing__Source__

#include <stdio.h>
#include "Color.h"
#include "Vector3.h"

class Source{
private:
public:
    Source();
    virtual Vector3 getLightPosition();
    virtual Color getColor();
};

#endif /* defined(__RayTracing__Source__) */
