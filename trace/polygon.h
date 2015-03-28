#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "ray.h"
#include "sceneobject.h"
#include "surface.h"

class Polygon : public SceneObject
{
    public:
        Polygon();
        Polygon(std::vector<Vector3> verts, Surface surf);
        bool intersect(Ray * ray);
        RGBAPixel shade(Ray * ray, std::vector<Light> lights, std::vector<SceneObject *> & objects,
                    RGBAPixel bgcolor, int depth, BVolume & scene);
        void setNormal();
        void setBounds();
        std::string str();

        std::vector<Vector3> vertices;
        Vector3 normal;
        Surface surface;

};

#endif