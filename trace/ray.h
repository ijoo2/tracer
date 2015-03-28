#pragma once

#include <vector>
#include "sceneobject.h"
#include "vector3.h"
#include "easypng.h"
#include "light.h"
#include "bvolume.h"

class BVolume;

class Ray
{
    public:
        Ray();
        Ray(Vector3 p, Vector3 v, int d);

        bool trace(std::vector<SceneObject *> objects);
        RGBAPixel shade(std::vector<Light> lights, std::vector<SceneObject *> objects, 
            RGBAPixel bgcolor, BVolume & scene);

        SceneObject * object;
        Vector3 anchor, dir;
        double t;
        int depth;
};
