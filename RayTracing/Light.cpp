//
//  Light.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/26/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Light.h"

Light::Light():position(Vector3(0,0,0)),color(Color()){
}

Light::Light(Vector3 pos,Color col):position(pos),color(col){
}

Vector3 Light::getLightPosition(){
    return position;
}

Color Light::getColor(){
    return color;
}