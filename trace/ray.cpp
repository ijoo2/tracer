#include "ray.h"

#define FAR_AWAY 1000000000000.0

using namespace std;

Ray::Ray()
{
    object = nullptr;
    anchor = Vector3();
    dir = Vector3();
    t = FAR_AWAY;
    depth = 0;
}


Ray::Ray(Vector3 p, Vector3 v, int d)
{
    object =  nullptr;
    anchor = p;
    dir = v;
    t = FAR_AWAY;
    depth = d;
}

bool Ray::trace(vector<SceneObject *> objects)
{
    if (depth > 2)
        return false;
    Ray * r = this;
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        SceneObject * e = objects[i];
        if (e->intersect(r))
            continue;
    }

    return (object != nullptr);
}

RGBAPixel Ray::shade(vector<Light> lights, vector<SceneObject *> objects,
    RGBAPixel bgcolor, BVolume & scene)
{
    //cout << "Calling " << object << ": "<<object->str() << "->shade()" << endl;
    return object->shade(this, lights, objects, bgcolor, depth, scene);
}