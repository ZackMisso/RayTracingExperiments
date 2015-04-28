//
//  Vector3.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Vector3.h"

Vector3::Vector3(number x,number y,number z):x(x),y(y),z(z){
}

// identity vectors
Vector3 Vector3::O(){return Vector3(0,0,0);}
Vector3 Vector3::X(){return Vector3(1,0,0);}
Vector3 Vector3::Y(){return Vector3(0,1,0);}
Vector3 Vector3::Z(){return Vector3(0,0,1);}

Vector3 Vector3::normalize(){
    number mag=sqrt(x*x+y*y+z*z);
    return Vector3(x/mag,y/mag,z/mag);
}

Vector3 Vector3::negative(){
    return Vector3(-x,-y,-z);
}

Vector3 Vector3::cross(Vector3 b){
    return Vector3(y*b.getZ()-z*b.getY(),z*b.getX()-x*b.getZ(),x*b.getY()-y*b.getX());
}

Vector3 Vector3::add(Vector3 b){
    return Vector3(x+b.getX(),y+b.getY(),z+b.getZ());
}

Vector3 Vector3::mult(number scalar){
    return Vector3(x*scalar,y*scalar,z*scalar);
}

number Vector3::dot(Vector3 b){
    return x*b.getX()+y*b.getY()+z*b.getZ();
}

number Vector3::magnitude(){
    return sqrt(x*x+y*y+z*z);
}