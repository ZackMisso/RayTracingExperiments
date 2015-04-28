//
//  Camera.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Camera.h"

Camera::Camera():
cameraPos(Vector3(0,0,0)),cameraDir(Vector3(0,0,1)),cameraRight(Vector3(0,0,0)),cameraDown(Vector3(0,0,0)){
}

Camera::Camera(Vector3 pos,Vector3 dir,Vector3 right,Vector3 down):
cameraRight(right),cameraDown(down),cameraDir(dir),cameraPos(pos){
}