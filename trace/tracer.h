#pragma once
#ifndef TRACER_H
#define TRACER_H

#include <vector>
#include "easypng.h"
#include "sceneobject.h"
#include "light.h"
#include "ray.h"
#include "bvolume.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class Tracer
{
    public:
        Tracer();
        Tracer(BVolume & sceneobjs, std::vector<Light> l, PNG * scr,
               RGBAPixel bg);
        void set_view(Vector3 eye, Vector3 lookAt, Vector3 up, double fov);
        PNG * render(Vector3 eye);

        BVolume scene;
        std::vector<Light> lights;
        PNG * image;
        int width, height;
        RGBAPixel background;
        Vector3 look, v, u, vp;
};

RGBAPixel avgColor(std::vector<RGBAPixel> colors);

#endif