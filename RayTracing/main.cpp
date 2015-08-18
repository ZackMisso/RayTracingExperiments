//
//  main.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Scene.h"

int main(int argc, const char * argv[]) {
    Scene *scene=new Scene();
    scene->render();
    return 0;
}
