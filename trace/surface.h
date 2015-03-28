#pragma once
#ifndef SURFACE_H
#define SURFACE_H

#include "ray.h"
#include "sceneobject.h"
#include "light.h"
#include <vector>
#include <math.h>
#include "bvolume.h"

class Surface
{
    public:
        Surface();
        Surface(RGBAPixel c, float amb, float diff, float spec, float ref);

        RGBAPixel shade(Vector3 p, Vector3 v, Vector3 n,
            std::vector<Light> lights, std::vector<SceneObject*> & objects,
            RGBAPixel bgcolor, int depth, Ray * ray, BVolume & scene);

        float ka, kd, ks, kr;
        RGBAPixel color;

};

int min(int a, int b);

#endif