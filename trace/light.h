#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#define AMBIENT 0
#define DIRECTIONAL 1
#define POINT 2

#include "easypng.h"
#include "vector3.h"

class Light
{
    public:
        Light();
        Light(int type, RGBAPixel c, Vector3 v);
        Light(int type, RGBAPixel c);

        int _type;
        RGBAPixel color;
        Vector3 dir;

};

#endif