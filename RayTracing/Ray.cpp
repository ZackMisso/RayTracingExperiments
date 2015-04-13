//
//  Ray.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Ray.h"

Ray::Ray():origin(Vector3(0,0,0)),direction(Vector3(1,0,0)){
}

Ray::Ray(Vector3 origin,Vector3 direction):origin(origin),direction(direction){
}