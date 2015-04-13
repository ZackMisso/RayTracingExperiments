//
//  Source.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 4/11/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Source.h"

Source::Source(){
}

Color Source::getColor(){
    return Color(1.0,1.0,1.0,0.0);
}

Vector3 Source::getLightPosition(){
    return Vector3(0.0,0.0,0.0);
}