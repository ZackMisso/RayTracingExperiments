//
//  main.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/21/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

// Note :: I am currently following an online tutorial so please forgive some of the bad programming
// practices. I will be changing this soon;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Entity.h"
#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include "Source.h"
#include "Scene.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    /*std::cout << "Hello, World!\n";
    int dpi=72;
    int width=640;
    int height=480;
    number aspectratio=(number)width/(number)height;
    number ambientLight=.3;
    number accuracy=.0000001;
    RGBPixel *pixels=new RGBPixel[width*height];
    Vector3 campos(3,1.5f,-4);
    Vector3 O(0,0,0);
    Vector3 X(1,0,0);
    Vector3 Y(0,1,0);
    Vector3 Z(0,0,1);
    Vector3 lookAt(0,0,0);
    Vector3 diffBtw(campos.getX()-lookAt.getX(),campos.getY()-lookAt.getY(),campos.getZ()-lookAt.getZ());
    Vector3 camDir=diffBtw.negative().normalize();
    Vector3 camRight=Y.cross(camDir).normalize();
    Vector3 camDown=camRight.cross(camDir);
    Camera camera(campos,camDir,camRight,camDown);
    Color whiteLight(1.0f,1.0f,1.0f,0.0f);
    Color niceGreen(.5f,1.0f,.5f,.3f);
    Color maroon(.5f,.25f,.25f,0);
    Color grey(.5f,.5f,.5f,0.0f);
    Color black(0.0f,0.0f,0.0f,0.0f);
    Vector3 lightPosition(-7,10,-7);
    Light sceneLight(lightPosition,whiteLight);
    std::vector<Source*> lightSources;
    lightSources.push_back(dynamic_cast<Source*>(&sceneLight));
    // scene objects
    Sphere sphere(O,niceGreen,1.0f);
    Plane floor(Y,maroon,-1.0f);
    std::vector<Entity*> sceneEntities;
    sceneEntities.push_back(dynamic_cast<Entity*>(&sphere));
    sceneEntities.push_back(dynamic_cast<Entity*>(&floor));
    number xamnt;
    number yamnt;
    int temp=0;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            // start with no anti-aliasing
            if(width>height){
                xamnt=((x+.5f)/width)*aspectratio-(((width-height)/(number)height)/2);
                yamnt=((height-y)+.5f)/height;
            }else if(height>width){
                xamnt=(x+.5f)/width;
                yamnt=(((height-y)+.5f)/height)/aspectratio-(((height-width)/(number)width)/2);
            }else{
                xamnt=(x+.5f)/width;
                yamnt=((height-y)+.5f)/height;
            }
            Vector3 cameraRayOrigin=camera.getCameraPos();
            Vector3 cameraRayDirection=camDir.add(camRight.mult(xamnt-.5f).add(camDown.mult(yamnt-.5f))).normalize();
            Ray cameraRay(cameraRayOrigin,cameraRayDirection);
            std::vector<number> intersections;
            for(int index=0;index<sceneEntities.size();index++){
                intersections.push_back(sceneEntities.at(index)->findIntersection(cameraRay));
            }
            int indexOfMajorObject=winningObjectIndex(intersections);
            temp=y*width+x;
            //pixels[temp].r=100;
            //pixels[temp].g=0;
            //pixels[temp].b=0;
            if(indexOfMajorObject==-1){
                // set the background black
                pixels[temp].r=0;
                pixels[temp].g=0;
                pixels[temp].b=0;
            }else{
                // index corresponds to object
                if(intersections.at(indexOfMajorObject)>accuracy){
                    Vector3 intersectionPos=cameraRayOrigin.add(cameraRayDirection.mult(intersections.at(indexOfMajorObject)));
                    Vector3 intersectingRayDirection=cameraRayDirection; // changes during reflections
                    Color intersectionColor=getColorAt(intersectionPos,intersectingRayDirection,sceneEntities,lightSources,accuracy,ambientLight);
                    pixels[temp].r=intersectionColor.getRed();
                    pixels[temp].g=intersectionColor.getGreen();
                    pixels[temp].b=intersectionColor.getBlue();
                }
            }
        }
    }
    std::cout<<"Drawing Image\n";
    saveAsBMP("picTake6.bmp",width,height,dpi,pixels);
    std::cout<<"Drew Image\n";*/
    Scene *scene=new Scene();
    scene->render();
    return 0;
}
