#define _CRT_SECURE_NO_WARNINGS

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
#include <ctime>

#define PI 3.141592653 

using namespace std;

int main()
{
    int mult = 50;
    int width = 16*mult;
    int height = 9*mult;
    double fov = 120.0;

    vector<Light> lights;
    
    RGBAPixel background = RGBAPixel(0, 0, 0);
    RGBAPixel scolor1 = RGBAPixel(70, 120, 200);
    RGBAPixel grey = RGBAPixel(50, 50, 50);
    RGBAPixel lcolor1 = RGBAPixel(25, 25, 25);
    RGBAPixel red = RGBAPixel(255, 155, 75);
    RGBAPixel bright = RGBAPixel(255, 255, 250);
    RGBAPixel dim = RGBAPixel(5, 5, 3);

    double theta = 90.0;
    double phi = 90.0;
    Mesh mesh = Mesh(Vector3(0, 0, 0.0));
    mesh._load_mesh("shuttle.obj");

    Surface s1 = Surface(scolor1, .005, .99, .8, .05);
    Surface s2 = Surface(grey, .006, .99, .8, .8);
    Surface s3 = Surface(grey, .006, .99, .8, .8);
    Surface s4 = Surface(red, .006, .99, .8, .2);
    Surface s5 = Surface(bright, .006, .99, .001, 0.0);
    Surface earth = Surface(scolor1, .01, 2.2, 0.1, .05);
    Surface ps5 = Surface(lcolor1, .006, .99, .001, 0.0);


    Vector3 sunpos = Vector3(0, 0.0, 14960.0);
    Vector3 earthpos = Vector3(0.0, 0.0, 0.0);

    SceneObject * sphere = new Sphere(10.0, Vector3(0.0, 0.0, 0.0), s3);
    SceneObject * sphere2 = new Sphere(5.0, Vector3(10, -5, -10.0), s2);
    SceneObject * sphere3 = new Sphere(6371.0, earthpos, earth);
    SceneObject * sphere4 = new Sphere(695800.0, sunpos, s5);
    SceneObject * plane1 = new Plane(Vector3(0.0, -10.0, 0.0), Vector3(0.0, 1.0, 0.0), ps5);
    SceneObject * plane2 = new Plane(Vector3(0.0, 10.0, -20.0), Vector3(0.0, 0.0, -1.0), ps5);
    SceneObject * sunplane = new Plane(sunpos.add(Vector3(0,0, 2)), Vector3(0.0, 0.0, 1.0), ps5);

    Vector3 lv = earthpos.subtract(sunpos);
    lv.normalize();

    vector<SceneObject *> objects = mesh._create_polygons(s2);
    
    

    //objects.push_back(sphere);
    //objects.push_back(sphere2);
    //objects.push_back(sphere3);
    //objects.push_back(sphere4);
    objects.push_back(plane1);
    //objects.push_back(plane2);
    //objects.push_back(sunplane);
    
    Light l1 = Light(0, lcolor1);
    Light l2 = Light(2, lcolor1, Vector3(-1.0, 55.0, 2.0));
    Light l2_1 = Light(2, lcolor1, Vector3(1.0, 55.0, 2.0));
    Light l2_2 = Light(2, lcolor1, Vector3(0.0, 55.0, 2.0));
    Light l3 = Light(1, grey, Vector3(0.0, -1.0, 0.0));
    Light l4 = Light(2, dim, Vector3(2.75, 5.50, -2.75));
    Light l5 = Light(2, dim, Vector3(2.80, 5.50, -2.75));
    Light l6 = Light(2, dim, Vector3(2.75, 5.50, -2.75));
    Light l7 = Light(2, dim, Vector3(2.70, 5.50, -2.75));
    Light sun = Light(1, lcolor1, lv);
    Light sun2 = Light(2, bright, sunpos);
    
    lights.push_back(l1);
    lights.push_back(l2);
    lights.push_back(l2_1);
    lights.push_back(l2_2);
    lights.push_back(l3);
    //lights.push_back(l4);
    //lights.push_back(l5);
    //lights.push_back(l6);
    //lights.push_back(l7);
    //lights.push_back(sun2);
    //lights.push_back(sun2);
    //lights.push_back(sun2);
    //lights.push_back(sun2);

    Vector3 eye = Vector3(0, 0, 10);
    Vector3 lookAt = Vector3();//earthpos;//Vector3(2.75, 2.75, 0);
    Vector3 up = Vector3(0.0, 1.0, 0.0);

    BVolume bvscene(objects);

    PNG * image =  new PNG(width, height);
    Tracer testdraw = Tracer(bvscene, lights, image, background);
    testdraw.set_view(eye, lookAt, up, fov);

    time_t start, end;
    double delta = 0;
    start = time(NULL);
    image = testdraw.render(eye);
    end = time(NULL);
    delta = end-start;
    cout << delta << endl;


    image->writeToFile("test.png");
    delete image;
    mesh._clear_polygons(objects);
    //system("pause");
    return 0;
}