#include "polygon.h"
#include "plane.h"

using namespace std;

Polygon::Polygon() : normal(Vector3()), surface(Surface()) {}

Polygon::Polygon(vector<Vector3> verts,  Surface surf) : vertices(verts),
    surface(surf)
{
    setNormal();
    minX = minY = minZ = INT_MAX;
    maxX = maxY = maxZ = -INT_MAX;
    setBounds();
}

bool Polygon::intersect(Ray * ray)
{
    double d_dot_n = ray->dir.dot(normal);
    if (d_dot_n == 0)
        return false;
    
    double t = -(ray->anchor.subtract(vertices[0])).dot(normal)/d_dot_n;

    if (t >= ray->t)
        return false;
    
    if (t < 0)
        return false;

    Vector3 r = Vector3(ray->dir.x, ray->dir.y, ray->dir.z);
    r.normalize();
    r.scale(t);

    Vector3 x = ray->anchor.add(r);

    for (int i = 0; i < vertices.size(); i++)
    {
        Vector3 a, b;
        a = vertices[i % vertices.size()];
        b = vertices[(i+1) % vertices.size()];
        Vector3 ab = b.subtract(a);
        Vector3 ax = x.subtract(a);
        if (cross(ab, ax).dot(normal) >= 0)
            continue;
        else
            return false;
    }

    ray->t = t;
    ray->object = this;
    return true;
}

RGBAPixel Polygon::shade(Ray * ray, vector<Light> lights, vector<SceneObject *> & objects,
    RGBAPixel bgcolor, int depth, BVolume & scene)
{
    ray->dir.scale(ray->t);
    Vector3 p = ray->anchor.add(ray->dir);
    Vector3 v = Vector3(-ray->dir.x, -ray->dir.y, -ray->dir.z);
    v.normalize();

    return surface.shade(p, v, normal, lights, objects, bgcolor, depth, ray, scene);
}

void Polygon::setNormal()
{
    Vector3 a, b, c;
    a = vertices[0];
    b = vertices[1];
    c = vertices[2];

    Vector3 v1 = b.subtract(a);
    Vector3 v2 = c.subtract(a);

    Vector3 n = cross(v1, v2);
    n.normalize();
    normal = n;
}

void Polygon::setBounds()
{
    for each (auto vert in vertices)
    {
        if (vert.x <= minX)
            minX = vert.x;
        else if (vert.x > maxX)
            maxX = vert.x;
        else {}
        
        if (vert.y <= minY)
            minY = vert.y;
        else if (vert.y > maxY)
            maxY = vert.y;
        else {}

        if (vert.z <= minZ)
            minZ = vert.z;
        else if (vert.z > maxZ)
            maxZ = vert.z;
        else {}
    }

}

string Polygon::str()
{
    return "Polygon";
}