#include "tracer.h"
#define PI 3.141592653

using namespace std;

Tracer::Tracer() : scene(BVolume()), lights(vector<Light>()), image(nullptr),
    width(0), height(0), background(RGBAPixel(0,0,0)), look(Vector3()),
    v(Vector3()), u(Vector3()), vp(Vector3()) {}

Tracer::Tracer(BVolume & sceneobjs, vector<Light> l, PNG * scr,
               RGBAPixel bg) : scene(sceneobjs), lights(l), image(scr),
               width(scr->width()), height(scr->height()), background(bg),
               look(Vector3()), u(Vector3()), vp(Vector3()) {}



/*
Takes input eye vector, look at vector, up vector, fov angle.
    eye - The anchor point of all starting rays.
    lookat - The point at which the eye looks at.
    up - the arbitrary direction defining what is "up".

Creates an orthonormal basis for the scene,
so that vectors u, v, and up are all orthogonal
to each other.

Sets the view point for the scene using
the orthonormal basis and the field of view.
*/
void Tracer::set_view(Vector3 eye, Vector3 lookAt, Vector3 up, double fov)
{
    look = lookAt.subtract(eye);

    double field = (width/(2*tan(.5*fov*PI/180)));

    u = cross(look, up);
    u.normalize();
    v = cross(look, u);
    v.normalize();
    look.normalize();

    vp = look;
    vp.x = vp.x*field - .5*(width*u.x + height*v.x);
    vp.y = vp.y*field - .5*(width*u.y + height*v.y);
    vp.z = vp.z*field - .5*(width*u.z + height*v.z);
}

/*
Takes input eye coordinate and computes 
the ray to be used for tracing each pixel.

Iterates through pixels i, j and calculates
the color for that pixel as an average of 5 samples
stratified over 4 'corners' and the center.

Returns PNG image
*/
PNG * Tracer::render(Vector3 eye)
{
    cout << "Width: " << width << "px" << endl;
    cout << "Height: " << height << "px" << endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            
            vector<Vector3> Dir;
            float i1, i2;
            float j1, j2;
            i1 = i - 0.5;
            i2 = i + 0.5;
            j1 = j - 0.5;
            j2 = j + .05;

            RGBAPixel p;
            Vector3 d = Vector3(i*u.x + j*v.x + vp.x,
                                i*u.y + j*v.y + vp.y,
                                i*u.z + j*v.z + vp.z);

            Vector3 d1 = Vector3(i1*u.x + j1*v.x + vp.x,
                                i1*u.y + j1*v.y + vp.y,
                                i1*u.z + j1*v.z + vp.z);

            Vector3 d2 = Vector3(i1*u.x + j2*v.x + vp.x,
                                i1*u.y + j2*v.y + vp.y,
                                i1*u.z + j2*v.z + vp.z);
            
            Vector3 d3 = Vector3(i2*u.x + j1*v.x + vp.x,
                                i2*u.y + j1*v.y + vp.y,
                                i2*u.z + j1*v.z + vp.z);
            
            Vector3 d4 = Vector3(i2*u.x + j2*v.x + vp.x,
                                i2*u.y + j2*v.y + vp.y,
                                i2*u.z + j2*v.z + vp.z);

            d.normalize();
            d1.normalize();
            d2.normalize();
            d3.normalize();
            d4.normalize();
            
            Dir.push_back(d);
            Dir.push_back(d1);
            Dir.push_back(d2);
            Dir.push_back(d3);
            Dir.push_back(d4);

            vector<RGBAPixel> colors;
            for each (auto dir in Dir)
            {
                Ray ray = Ray(eye, dir, 0);
                //scene.intersect(&ray);
                vector<SceneObject *> objects = scene.root->objects;
                //vector<SceneObject *> objects = scene.candidates;
                if (ray.trace(objects))
                {
                    p = ray.shade(lights, objects, background, scene);
                    colors.push_back(p);

                }
                else
                {
                    colors.push_back(background);
                }
            }
        
            *(*image)(i,j) = avgColor(colors);
        }
    }
    return image;
}

RGBAPixel avgColor(vector<RGBAPixel> colors)
{
    int r, g, b;
    r = 0;
    g = 0;
    b = 0;
    for each (auto color in colors)
    {
        r += color.red;
        g += color.green;
        b += color.blue;
    }

    float size = (float) colors.size();
    return RGBAPixel(r/size, g/size, b/size);
}