//
//  Plane.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 4/10/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Plane.h"

Plane::Plane():normal(Vector3(1,0,0)),color(.5f,.5f,.5f,0),distance(0){
}

Plane::Plane(Vector3 norm,Color col,number dist):normal(norm),color(col),distance(dist){
}

Vector3 Plane::getPlaneNormal(){
    return normal;
}

Color Plane::getColor(){
    return color;
}

number Plane::getDistance(){
    return distance;
}

Vector3 Plane::getNormalAt(Vector3 point){
    return normal;
}

number Plane::findIntersection(Ray ray){
    Vector3 rayDirection=ray.getDirection();
    number a=rayDirection.dot(normal);
    if(a==0){
        // ray is parallel to the plane
        return -1;
    }
    else{
        number b=normal.dot(ray.getOrigin().add(normal.mult(distance).negative()));
        return -1*b/a;
    }
}