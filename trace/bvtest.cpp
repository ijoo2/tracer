#include "easypng.h"
#include "light.h"
#include "vector3.h"
#include "surface.h"
#include "sphere.h"
#include "polygon.h"
#include "plane.h"
#include "ray.h"
#include "sceneobject.h"
#include "tracer.h"
#include "mesh.h"
#include "bvolume.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int _ain()
{
    RGBAPixel scolor1 = RGBAPixel(70, 120, 200);
    Mesh mesh = Mesh(Vector3(0, 0, 0.0));
    mesh._load_mesh("shuttle.obj");
    Surface s1 = Surface(scolor1, .005, .99, .8, .05);
    vector<SceneObject *> objects = mesh._create_polygons(s1);

    cout << objects.size() << endl;
    BVolume bvscene(objects);
    
    Ray r = Ray(Vector3(0,0,-20), Vector3(0,0,1), 0);
    
    bvscene.intersect(&r);
    cout << bvscene.candidates.size() << endl;

    return 0;
}