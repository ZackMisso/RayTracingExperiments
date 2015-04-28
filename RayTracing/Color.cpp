//
//  Color.cpp
//  RayTracing
//
//  Created by Zackary T Misso on 3/26/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#include "Color.h"

Color::Color():red(0.5f),green(0.5f),blue(0.5f),special(0.0f){
}

Color::Color(number r,number g,number b,number s):red(r),green(g),blue(b),special(s){
}

Color Color::colorScalar(number val){
    return Color(red*val,green*val,blue*val,special);
}

Color Color::colorAdd(Color other){
    return Color(red+other.getRed(),green+other.getGreen(),blue+other.getBlue(),special);
}

Color Color::colorMult(Color other){
    return Color(red*other.getRed(),green*other.getGreen(),blue*other.getBlue(),special);
}

Color Color::colorAverage(Color other){
    return Color((red+other.getRed())/2,(green+other.getGreen())/2,(blue+other.getBlue())/2,special);
}

Color Color::clip(){
    number alllight=red+blue+green;
    number excessLight=alllight-3;
    if(excessLight>0){
        red=red+excessLight*(red/alllight);
        green=green+excessLight*(green/alllight);
        blue=blue+excessLight*(blue/alllight);
    }
    if(red>1)
        red=1;
    if(green>1)
        green=1;
    if(blue>1)
        blue=1;
    if(red<0)
        red=0;
    if(green<0)
        green=0;
    if(blue<0)
        blue=0;
    return Color(red,green,blue,special);
}

number Color::brightness(){return (red+green+blue)/3;}

// pre-set Colors
Color Color::whiteLight(){return Color(1.0f,1.0f,1.0f,0.0f);}
Color Color::niceGreen(){return Color(.5f,1.0f,.5f,.3f);}
Color Color::maroon(){return Color(.5f,.25f,.25f,0);}
Color Color::grey(){return Color(.5f,.5f,.5f,0.0f);}
Color Color::black(){return Color(0.0f,0.0f,0.0f,0.0f);}

// getter methods
number Color::getRed(){return red;}
number Color::getGreen(){return green;}
number Color::getBlue(){return blue;}
number Color::getSpecial(){return special;}

// setter methods
void Color::setRed(number r){red=r;}
void Color::setGreen(number g){green=g;}
void Color::setBlue(number b){blue=b;}
void Color::setSpecial(number s){special=s;}