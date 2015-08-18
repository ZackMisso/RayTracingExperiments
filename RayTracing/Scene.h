//
//  Scene.h
//  RayTracing
//
//  Created by Zackary T Misso on 4/13/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Scene__
#define __RayTracing__Scene__

#include <stdio.h>
#include <vector>
#include "Vector3.h"
#include "Color.h"
#include "Source.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

struct RGBPixel{
    number r;
    number g;
    number b;
};

class Scene{
private:
    RGBPixel *pixels;
    std::vector<Source*> *lightSources;
    std::vector<Entity*> *sceneEntities;
    const char * fileName;
    number aspectRatio;
    number ambientLight;
    number accuracy;
    Camera *camera;
    int width;
    int height;
    int temp; // ? Why ?
    int indexOfMinValue; // ? Why ?
    void initializeDefaults();
public:
    Scene();
    ~Scene();
    void saveAsBMP(const char *fileName,int width,int height,int dpi,RGBPixel *data);
    int winningObjectIndex(std::vector<number> entity_intersections);
    Color getColorAt(Vector3 intersectionPos,Vector3 intersectingRayDirection);
    void render();
    
    // setter methods
    void setLightSources(std::vector<Source*> *param);
    void setSceneEntities(std::vector<Entity*> *param);
    void setFileName(const char * param);
    void setAspectRatio(number param);
    void setAmbientLight(number param);
    void setAccuracy(number param);
    void setCamera(Camera *param);
    void setHeight(int param);
    void setWidth(int param);
};

#endif /* defined(__RayTracing__Scene__) */
