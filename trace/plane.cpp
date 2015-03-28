#include "plane.h"

using namespace std;

//Default constructor: Plane at origin with +y normal vector with default surface
Plane::Plane() : point(Vector3()), normal(Vector3(0.0, 1.0, 0.0)), surface(Surface()) {}

Plane::Plane(Vector3 p, Vector3 n, Surface surf) : point(p), normal(n), surface(surf) {}

bool Plane::intersect(Ray * ray)
{
    double d_dot_n = ray->dir.dot(normal);
    if (d_dot_n == 0)
        return false;
    
    double t = (point.subtract(ray->anchor)).dot(normal)/d_dot_n;
    t = -((ray->anchor.subtract(point)).dot(normal))/d_dot_n;
    //t = -(ray->anchor.dot(normal) + normal.dot(point)/d_dot_n;

    if (t > ray->t)
        return false;
    
    if (t < 0)
        return false;
    
    if (t > 0)
    {
        ray->t = t;
        ray->object = this;
        return true;
    }

    return false;
}

RGBAPixel Plane::shade(Ray * ray, vector<Light> lights, vector<SceneObject *> & objects, 
    RGBAPixel bgcolor, int depth, BVolume & scene)
{
    ray->dir.scale(ray->t);
    Vector3 p = ray->anchor.add(ray->dir);
    Vector3 v = Vector3(-ray->dir.x, -ray->dir.y, -ray->dir.z);
    v.normalize();
    return surface.shade(p, v, normal, lights, objects, bgcolor, depth, ray, scene);
}

string Plane::str()
{
    return "Plane";
}
