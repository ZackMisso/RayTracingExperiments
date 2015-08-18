//
//  Scene.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 4/13/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Scene.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>


Scene::Scene(){
    initializeDefaults();
}

Scene::~Scene(){
    // implement
}


// default scene with a floor and a single sphere
void Scene::initializeDefaults(){
    sceneEntities=new std::vector<Entity*>(2);
    lightSources=new std::vector<Source*>(1);
    width=640;
    height=480;
    aspectRatio=(number)width/(number)height;
    ambientLight=.3;
    accuracy=.0000001;
    Vector3 campos(3,1.5f,-4);
    Vector3 lookAt(0,0,0);
    // get the vector from where the camera is looking to the camera
    Vector3 diffBtw(lookAt.getX()-campos.getX(),lookAt.getY()-campos.getY(),lookAt.getZ()-campos.getZ());
    Vector3 camDir=diffBtw.normalize();
    // get the vector perpendicular to the camera direction and y identity vector
    // i.e, the vector going to the side from the camera direction
    Vector3 camRight=Vector3::Y().cross(camDir).normalize();
    // get the vector perpendicular to the camera, the right of the camera, and the y identity vector
    // i.e. the vector going down from he camera direction
    Vector3 camDown=camRight.cross(camDir);
    // create the camera
    camera=new Camera(campos,camDir,camRight,camDown);
    // create the light
    Vector3 lightPosition(-7,10,-7);
    Light *sceneLight=new Light(lightPosition,Color::whiteLight());
    lightSources->at(0)=dynamic_cast<Source*>(sceneLight);
    // create the scene entities
    Sphere *sphere=new Sphere(Vector3::O(),Color::niceGreen(),1.0f);
    Plane *floor=new Plane(Vector3::Y(),Color::maroon(),1.0f);
    pixels=new RGBPixel[width*height];
    sceneEntities->at(0)=dynamic_cast<Entity*>(sphere);
    sceneEntities->at(1)=dynamic_cast<Entity*>(floor);
}

void Scene::saveAsBMP(const char *fileName,int width,int height,int dpi,RGBPixel *data){
    // draws the image and saves it to a file
    FILE *file;
    int area=width*height;
    int s=area*4;
    std::cout<<s<<" Area\n";
    int fileSize=54+s;
    number factor=39.375;
    int ppm=dpi*static_cast<int>(factor);
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

int Scene::winningObjectIndex(std::vector<number> entity_intersections){
    number max=-1.0f;
    std::vector<number>::iterator itr=entity_intersections.begin();
    int num=0;
    for(;itr!=entity_intersections.end();itr++,num++)
        if((max>*itr&&*itr>0)||max<0.0f){
            max=*itr;
            indexOfMinValue=num;
        }
    if(max>0)
        return indexOfMinValue;
    return -1;
}


// inefficient - Does not cull scene entities
Color Scene::getColorAt(Vector3 intersectionPos,Vector3 intersectingRayDirection){
    Color objectColor=sceneEntities->at(indexOfMinValue)->getColor();
    Vector3 objectNormal=sceneEntities->at(indexOfMinValue)->getNormalAt(intersectionPos);
    Color finalColor=objectColor.colorScalar(ambientLight);
    for(int lightIndex=0;lightIndex<lightSources->size();lightIndex++){
        Vector3 lightDirection=lightSources->at(lightIndex)->getLightPosition().add(intersectionPos.negative()).normalize();
        number cosineAngle=objectNormal.dot(lightDirection);
        if(cosineAngle>0){
            // test for shadows
            char shadowed=0;
            Vector3 distToLight=lightSources->at(lightIndex)->getLightPosition().add(intersectionPos.negative()).normalize();
            number distToLightMag=distToLight.magnitude();
            Ray *shadowRay= new Ray(intersectionPos,lightSources->at(lightIndex)->getLightPosition().add(intersectionPos.negative()).normalize());
            std::vector<number> secondaryIntersections;
            for(int entityIndex=0;entityIndex<sceneEntities->size()&&!shadowed;entityIndex++)
                secondaryIntersections.push_back(sceneEntities->at(entityIndex)->findIntersection(shadowRay));
            for(int c=0;c<secondaryIntersections.size();c++)
                if(secondaryIntersections.at(c)>accuracy){
                    if(secondaryIntersections.at(c)<=distToLightMag)
                        shadowed=1;
                    break;
                }
            if(!shadowed){
                finalColor=finalColor.colorAdd(objectColor.colorMult(lightSources->at(lightIndex)->getColor()).colorScalar(cosineAngle));
                if(objectColor.getSpecial()>0&&objectColor.getSpecial()<=1){
                    number dot1=objectNormal.dot(intersectingRayDirection.negative());
                    Vector3 scalar1=objectNormal.mult(dot1);
                    Vector3 add1=scalar1.add(intersectingRayDirection);
                    Vector3 scalar2=add1.mult(2);
                    Vector3 add2=intersectingRayDirection.negative().add(scalar2);
                    Vector3 reflectionDirection=add2.normalize();
                    number specular=reflectionDirection.dot(lightDirection);
                    if(specular>0){
                        specular=powf(specular,10);
                        finalColor.colorAdd(lightSources->at(lightIndex)->getColor().colorScalar(specular*objectColor.getSpecial()));
                    }
                }
            }
        }
    }
    return finalColor.clip();
}

void Scene::render(){
    number xamnt=0.0f;
    number yamnt=0.0f;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            // start with no anti-aliasing
            // these branches could be very inefficient later on.
            if(width>height){
                xamnt=((x+.5f)/width)*aspectRatio-(((width-height)/(number)height)/2);
                yamnt=((height-y)+.5f)/height;
            }else if(height>width){
                xamnt=(x+.5f)/width;
                yamnt=(((height-y)+.5f)/height)/aspectRatio-(((height-width)/(number)width)/2);
            }else{
                xamnt=(x+.5f)/width;
                yamnt=((height-y)+.5f)/height;
            }
            Vector3 cameraRayOrigin=camera->getCameraPos();
            Vector3 cameraRayDirection=camera->getCameraDir().add(camera->getCameraRight().mult(xamnt-.5f).add(camera->getCameraDown().mult(yamnt-.5f))).normalize();
            Ray *cameraRay=new Ray(cameraRayOrigin,cameraRayDirection);
            std::vector<number> intersections(sceneEntities->size());
            int index=0;
            std::vector<Entity*>::iterator itr=sceneEntities->begin();
            for(;itr!=sceneEntities->end();itr++,index++)
                intersections.at(index)=((*itr)->findIntersection(cameraRay));
            int indexOfMajorObject=winningObjectIndex(intersections);
            temp=y*width+x;
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
                    Color intersectionColor=getColorAt(intersectionPos,intersectingRayDirection);
                    pixels[temp].r=intersectionColor.getRed();
                    pixels[temp].g=intersectionColor.getGreen();
                    pixels[temp].b=intersectionColor.getBlue();
                }
            }
        }
    }
    std::cout<<"Drawing Image\n";
    saveAsBMP("picTake9.bmp",width,height,72,pixels);
    std::cout<<"Drew Image\n";
}

// setter methods
void Scene::setLightSources(std::vector<Source*> *param){lightSources=param;}
void Scene::setSceneEntities(std::vector<Entity*> *param){sceneEntities=param;}
void Scene::setFileName(const char * param){fileName=param;}
void Scene::setAspectRatio(number param){aspectRatio=param;}
void Scene::setAmbientLight(number param){ambientLight=param;}
void Scene::setAccuracy(number param){accuracy=param;}
void Scene::setCamera(Camera *param){camera=param;}
void Scene::setHeight(int param){height=param;}
void Scene::setWidth(int param){width=param;}