#pragma once
#include <vector>
#include "ray.h"
#include "sceneobject.h"
#include "surface.h"
#include "light.h"

class Plane : public SceneObject
{
    public:
        Plane();
        Plane(Vector3 p, Vector3 n, Surface surf);
        bool intersect(Ray * ray);
        RGBAPixel shade(Ray * ray, std::vector<Light> lights, std::vector<SceneObject *> & objects,
                    RGBAPixel bgcolor, int depth, BVolume & scene);
        std::string str();

        Vector3 point, normal;
        Surface surface;

};

