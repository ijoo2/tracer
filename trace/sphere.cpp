#include "sphere.h"

using namespace std;

Sphere::Sphere() : center(Vector3()), r(1.0), surface(Surface())
{
    minX = minY = minZ = INT_MAX;
    maxX = maxY = maxZ = -INT_MAX;
    setBounds();
}

Sphere::Sphere(double rad, Vector3 c, Surface surf) : center(c), r(rad), surface(surf)
{
    minX = minY = minZ = INT_MAX;
    maxX = maxY = maxZ = -INT_MAX;
    setBounds();
}


//Ray-Sphere Intersection method
bool Sphere::intersect(Ray * ray)
{
    Vector3 cLine = center.subtract(ray->anchor);
    double dist = cLine.dot(ray->dir);

    if ((dist - r) > ray->t)
        return false;

    double t = r*r + dist*dist - (cLine._mag*cLine._mag);

    if (t < 0)
        return false;


    t = dist - sqrt(t);

    if (t > ray->t)
        return false;

    if (t < 0)
        return false;

    ray->t = t;
    ray->object = this;
    return true;

}

/*
Shade method specific for spheres, since
the normal vector for a point on its surface
is calculated differently.
*/
RGBAPixel Sphere::shade(Ray * ray, vector<Light> lights,
    vector<SceneObject *> & objects, RGBAPixel bgcolor, int depth, BVolume & scene)
{
    ray->dir.scale(ray->t);
    Vector3 p = ray->anchor.add(ray->dir);
    Vector3 v = Vector3(-ray->dir.x, -ray->dir.y, -ray->dir.z);
    Vector3 n = p.subtract(center);
    n.normalize();
    v.normalize();

    return surface.shade(p, v, n, lights, objects, bgcolor, depth, ray, scene);

}

/*
Sets the min, max pair of coordinates
that describe the minimum bounding volume 
that encloses this sphere.
*/
void Sphere::setBounds()
{
    minX = center.x - r;
    maxX = center.x + r;

    minY = center.y - r;
    maxY = center.y + r;

    minZ = center.z - r;
    maxZ = center.z + r;
}

/* 
For testing:
    inheritance
    scene accuracy
*/
string Sphere::str()
{
    return "Sphere";
}