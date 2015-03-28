#pragma once
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>
#include "light.h"
#include "easypng.h"

class Ray;
class BVolume;

class SceneObject
{
    public:
        SceneObject(){setBounds();};
        virtual ~SceneObject(){};

        virtual bool intersect(Ray *ray)
        {
            return false;
        };
        
        virtual RGBAPixel shade(Ray * ray, std::vector<Light> lights, std::vector<SceneObject *> & objects,
            RGBAPixel bgcolor, int depth, BVolume & scene)
        {
            return RGBAPixel();
        };

        virtual std::string str()
        {
            return std::string("SceneObject");
        };

        virtual void setBounds()
        {
            minX = minY = minZ = INT_MAX;
            maxX = maxY = maxZ = -INT_MAX;
        }

        virtual double operator[](int ind)
        {
            if (ind == 0)
                return maxX;
            else if (ind == 1)
                return maxY;
            else
                return maxZ;
        }

        double minX, minY, minZ, maxX, maxY, maxZ;
                  
};

#endif