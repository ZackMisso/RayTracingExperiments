//
//  Color.h
//  RayTracing
//
//  Created by Zackary T Misso on 3/26/15.
//  Copyright (c) 2015 Zackary Misso. All rights reserved.
//

#ifndef __RayTracing__Color__
#define __RayTracing__Color__

//#define number float
typedef double number;

class Color{
private:
    number red;
    number green;
    number blue;
    number special;
public:
    Color();
    Color(number r,number g,number b,number s);
    Color colorScalar(number val);
    Color colorAdd(Color other);
    Color colorMult(Color other);
    Color colorAverage(Color other);
    Color clip();
    number getRed();
    number getBlue();
    number getGreen();
    number getSpecial();
    number brightness();
    void setRed(number r);
    void setGreen(number g);
    void setBlue(number b);
    void setSpecial(number s);
    static Color whiteLight();
    static Color niceGreen();
    static Color maroon();
    static Color grey();
    static Color black();
    static Color redColor();
    static Color blueColor();
    static Color greenColor();
};

#endif /* defined(__RayTracing__Color__) */