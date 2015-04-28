//
//  Sphere.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 4/10/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere():position(Vector3(0,0,0)),radius(1.0f),color(Color(0.5f,0.5f,0.5f,0)){
}

Sphere::Sphere(Vector3 pos,Color col,number r):position(pos),color(col),radius(r){
}

number Sphere::findIntersection(Ray *ray){
    Vector3 rayOrigin=ray->getOrigin();
    number rayOriginX=rayOrigin.getX();
    number rayOriginY=rayOrigin.getY();
    number rayOriginZ=rayOrigin.getZ();
    Vector3 rayDirection=ray->getDirection();
    number rayDirectionX=rayDirection.getX();
    number rayDirectionY=rayDirection.getY();
    number rayDirectionZ=rayDirection.getZ();
    //Vector3 sphereCenter=position;
    number sphereCenterX=position.getX();
    number sphereCenterY=position.getY();
    number sphereCenterZ=position.getZ();
    //float a=1;
    number b=(2*(rayOriginX-sphereCenterX)*rayDirectionX);
    b+=(2*(rayOriginY-sphereCenterY)*rayDirectionY);
    b+=(2*(rayOriginZ-sphereCenterZ)*rayDirectionZ);
    number c=powf(rayOriginX-sphereCenterX,2)+powf(rayOriginY-sphereCenterY,2)+powf(rayOriginZ-sphereCenterZ,2)-radius*radius;
    number discriminant=b*b-4*c;
    if(discriminant>0){
        // the ray intersects the sphere
        // the first root
        number rootOne=((-1*b-sqrtf(discriminant))/2)-.000001;
        if(rootOne>0){
            return rootOne;
        }else{
            number rootTwo=((sqrtf(discriminant)-b)/2)-.000001;
            return rootTwo;
        }
    }else{
        // the ray misses
        return -1;
    }
}

Vector3 Sphere::getNormalAt(Vector3 point){
    // normal always points away from the center of a sphere
    Vector3 normal=point.add(position.negative()).normalize();
    return normal;
}

// getter methods
Vector3 Sphere::getPosition(){return position;}
Color Sphere::getColor(){return color;}
number Sphere::getRadius(){return radius;}