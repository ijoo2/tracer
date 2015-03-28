#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "sceneobject.h"
#include "light.h"
#include "surface.h"
#include <vector>
#include <string>

class Sphere : public SceneObject
{
    public:
        Sphere();
        Sphere(double rad, Vector3 c, Surface surf);
        bool intersect(Ray * ray);
        RGBAPixel shade(Ray * ray, std::vector<Light> lights, std::vector<SceneObject *>  & objects,
                    RGBAPixel bgcolor, int depth, BVolume & scene);

        std::string str();
        void setBounds();

        Vector3 center;
        double r;
        Surface surface;
};

#endif