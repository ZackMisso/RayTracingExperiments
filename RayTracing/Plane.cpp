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

Vector3 Plane::getNormalAt(Vector3 point){
    return normal;
}

number Plane::findIntersection(Ray *ray){
    Vector3 rayDirection=ray->getDirection();
    number a=rayDirection.dot(normal);
    if(a==0)
        // ray is perpendicular to the plane if the dot product is zero
        return -1;
    else{
        // why am I doing this again? This is doing nothing... Distiance is always -1...
        // nevermind, this is used for calculating the extra distance from the origin of the ray to the location of the plane.
        // in the future I should look into representing planes differently to avoid this... Adding a origin vector would be more efficient
        // This would not work for planes that are not axis-aligned
        Vector3 temp = normal.mult(distance);
        // add distance from world space origin to plane to the origin of the ray
        temp = ray->getOrigin().add(temp);
        // get the dot product between the normal and the vector to the origin of the plane
        number b = normal.dot(temp);
        //b=normal.dot(ray->getOrigin().add(normal.mult(distance).negative()));
        return -1*b/a;
    }
}

// getter methods
Vector3 Plane::getPlaneNormal(){return normal;}
Color Plane::getColor(){return color;}
number Plane::getDistance(){return distance;}