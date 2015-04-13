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


//Color getColorAt(Vector3 intersectionPos,Vector3 intersectingRayDirection,std::vector<Entity*>sceneObjects,std::vector<Light*> lightSources,float accuracy,float ambientLight);
    

struct RGBPixel{
    number r;
    number g;
    number b;
};

void saveAsBMP(const char *fileName,int width,int height,int dpi,RGBPixel *data){
    FILE *file;
    int area=width*height;
    int s=4*area;
    int fileSize=54+s;
    number factor=39.375;
    int m=static_cast<int>(factor);
    int ppm=dpi*m;
    unsigned char bmpFileHeader[14]={'B','M',0,0,0,0,0,0,0,0,54,0,0,0};
    unsigned char bmpInfoHeader[40]={40,0,0,0,0,0,0,0,0,0,0,0,1,0,24,0};
    bmpFileHeader[2]=(unsigned char)fileSize;
    bmpFileHeader[3]=(unsigned char)(fileSize>>8);
    bmpFileHeader[4]=(unsigned char)(fileSize>>16);
    bmpFileHeader[5]=(unsigned char)(fileSize>>24);
    bmpInfoHeader[4]=(unsigned char)(width);
    bmpInfoHeader[5]=(unsigned char)(width>>8);
    bmpInfoHeader[6]=(unsigned char)(width>>16);
    bmpInfoHeader[7]=(unsigned char)(width>>24);
    bmpInfoHeader[8]=(unsigned char)(height);
    bmpInfoHeader[9]=(unsigned char)(height>>8);
    bmpInfoHeader[10]=(unsigned char)(height>>16);
    bmpInfoHeader[11]=(unsigned char)(height>>24);
    bmpInfoHeader[21]=(unsigned char)(s);
    bmpInfoHeader[22]=(unsigned char)(s>>8);
    bmpInfoHeader[23]=(unsigned char)(s>>16);
    bmpInfoHeader[24]=(unsigned char)(s>>24);
    bmpInfoHeader[25]=(unsigned char)(ppm);
    bmpInfoHeader[26]=(unsigned char)(ppm>>8);
    bmpInfoHeader[27]=(unsigned char)(ppm>>16);
    bmpInfoHeader[28]=(unsigned char)(ppm>>24);
    bmpInfoHeader[29]=(unsigned char)(ppm);
    bmpInfoHeader[30]=(unsigned char)(ppm>>8);
    bmpInfoHeader[31]=(unsigned char)(ppm>>16);
    bmpInfoHeader[32]=(unsigned char)(ppm>>24);
    file=fopen(fileName,"wb");
    if(!file)
        std::cout<<"Failed\n";
    fwrite(bmpFileHeader,1,14,file);
    fwrite(bmpInfoHeader,1,40,file);
    for(int i=0;i<area;i++){
        RGBPixel pix=data[i];
        number red=pix.r*255;
        number blue=pix.b*255;
        number green=pix.g*255;
        unsigned char color[3]={(unsigned char)floor(blue),(unsigned char)floor(green),(unsigned char)floor(red)};
        fwrite(color,1,3,file);
    }
    fclose(file);
}

int temp;
int indexOfMinVal=-1;

int winningObjectIndex(std::vector<number> entity_intersections){
    // return the index of the winning intersection
    // prevent unnecessary calculations
    if(entity_intersections.size()==0){
        // if there are no intersections
        return -1;
    }
    else if(entity_intersections.size()==1){
        if(entity_intersections.at(0)>0){
            // if intersection is > 0 then this is it
            return 0;
        }else{
            return -1;
        }
    }else{
        // otherwise there is more than one intersection
        // first find the max value;
        number max=0.0f;
        for(int i=0;i<entity_intersections.size();i++){
            if(max<entity_intersections.at(i)){
                max=entity_intersections.at(i);
            }
        }
        if(max>0){
            for(int i=0;i<entity_intersections.size();i++){
                if(entity_intersections.at(i)<=max&&entity_intersections.at(i)>0){
                    max=entity_intersections.at(i);
                    indexOfMinVal=i;
                }
            }
            return indexOfMinVal;
        }
        return -1;
    }
}

Color getColorAt(Vector3 intersectionPos,Vector3 intersectingRayDirection,std::vector<Entity*>sceneObjects,std::vector<Source*> lightSources,number accuracy,number ambientLight){
    Color winningObjectColor=sceneObjects.at(indexOfMinVal)->getColor();
    Vector3 winningObjectNormal=sceneObjects.at(indexOfMinVal)->getNormalAt(intersectionPos);
    Color finalColor=winningObjectColor.colorScalar(ambientLight);
    for(int lightIndex=0;lightIndex<lightSources.size();lightIndex++){
        Vector3 lightDirection=lightSources.at(lightIndex)->getLightPosition().add(intersectionPos.negative()).normalize();
        number cosineAngle=winningObjectNormal.dot(lightDirection);
        if(cosineAngle>0){
            // test for shadows
            char shadowed=0;
            Vector3 distToLight=lightSources.at(lightIndex)->getLightPosition().add(intersectionPos.negative()).normalize();
            number distToLightMag=distToLight.magnitude();
            Ray shadowRay(intersectionPos,lightSources.at(lightIndex)->getLightPosition().add(intersectionPos.negative()).normalize());
            std::vector<number> secondaryIntersections;
            for(int entityIndex=0;entityIndex<sceneObjects.size()&&!shadowed;entityIndex++){
                secondaryIntersections.push_back(sceneObjects.at(entityIndex)->findIntersection(shadowRay));
            }
            for(int c=0;c<secondaryIntersections.size();c++){
                if(secondaryIntersections.at(c)>accuracy){
                    if(secondaryIntersections.at(c)<=distToLightMag){
                        shadowed=1;
                    }
                    break;
                }
                //break;
            }
            if(!shadowed){
                finalColor=finalColor.colorAdd(winningObjectColor.colorMult(lightSources.at(lightIndex)->getColor()).colorScalar(cosineAngle));
                if(winningObjectColor.getSpecial()>0&&winningObjectColor.getSpecial()<=1){
                    number dot1=winningObjectNormal.dot(intersectingRayDirection.negative());
                    Vector3 scalar1=winningObjectNormal.mult(dot1);
                    Vector3 add1=scalar1.add(intersectingRayDirection);
                    Vector3 scalar2=add1.mult(2);
                    Vector3 add2=intersectingRayDirection.negative().add(scalar2);
                    Vector3 reflectionDirection=add2.normalize();
                    number specular=reflectionDirection.dot(lightDirection);
                    if(specular>0){
                        specular=powf(specular,10);
                        finalColor.colorAdd(lightSources.at(lightIndex)->getColor().colorScalar(specular*winningObjectColor.getSpecial()));
                    }
                }
            }
        }
    }
    return finalColor.clip();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int dpi=72;
    int width=640;
    int height=480;
    number aspectratio=(number)width/(number)height;
    number ambientLight=.2f;
    number accuracy=.000001;
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
    saveAsBMP("picTake5.bmp",width,height,dpi,pixels);
    std::cout<<"Drew Image\n";
    return 0;
}
