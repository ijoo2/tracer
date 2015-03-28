#include "surface.h"

#define OFFSET .001

using namespace std;

Surface::Surface() : color(RGBAPixel()), ka(0.0), kd(0.0), ks(0.0), kr(0.0) {}

Surface::Surface(RGBAPixel c, float amb, float diff, float spec, float ref) : color(c),
    ka(amb), kd(diff), ks(spec), kr(ref) {}


RGBAPixel Surface::shade(Vector3 p, Vector3 v, Vector3 n,
            std::vector<Light> lights, std::vector<SceneObject *> & objects,
            RGBAPixel bgcolor, int depth, Ray * ray, BVolume & scene)
{
    double r = 0;
    double g = 0;
    double b = 0;

    double red = color.red;
    double green = color.green;
    double blue = color.blue;

    for (unsigned int i = 0; i < lights.size(); i++)
    {
        Light light = lights[i];
        double lred = light.color.red;
        double lgreen = light.color.green;
        double lblue = light.color.blue;
        
        //std::cout << light._type << std::endl;
        if (light._type == AMBIENT)
        {
            r += (ka*red*lred);
            g += (ka*green*lgreen);
            b += (ka*blue*lblue);
        }

        else
        {
            Vector3 l;
            double intensity = 1.0;
            double dsqr = INT_MAX;
            if (light._type == POINT)
            {
                l = light.dir.subtract(p);
                intensity = (lred*lred + lgreen*lgreen + lblue*lblue) / l.dot(l);
                dsqr = l.dot(l);
                l.normalize();
                
            }
            else
            {
                l = Vector3(-light.dir.x, -light.dir.y, -light.dir.z);
                l.normalize();
            }

            Vector3 shadowpoint = p.add(l.scalev(OFFSET));
            Ray shadowray = Ray(shadowpoint, l, depth+1);
            shadowray.t = sqrt(dsqr);
            
            scene.intersect(&shadowray);
            //vector<SceneObject *> shadowobjects = scene.root->objects;
            vector<SceneObject *> shadowobjects = scene.candidates;
            
            if (shadowray.trace(shadowobjects))
            {
                continue;
            }

            float cos = n.dot(l);
            if (cos > 0)
            {
                float diffuse = kd*cos;
                r += (kd*lred*intensity);
                g += (kd*lgreen*intensity);
                b += (kd*lblue*intensity);
            }

            if (ks > 0)
            {
                cos *= 2;
                Vector3 u = n.scalev(cos).subtract(l);
                double specular = v.dot(u);
                if (specular > 0)
                {
                    specular = ks*pow(abs(specular), 2.2);
                    r += (specular*lred*intensity);
                    g += (specular*lgreen*intensity);
                    b += (specular*lblue*intensity);
                }
            }

        }
    }

    if (kr > 0)
    {
        double t = v.dot(n);
        if (t > 0)
        {
            t *= 2;
            Vector3 reflect = n.scalev(t).subtract(v);
            Vector3 shadowpos = p.add(reflect.scalev(OFFSET));
            Ray refray = Ray(shadowpos, reflect, depth+1);
            //scene.intersect(&refray);
            vector<SceneObject *> refobjects = scene.root->objects;
            //vector<SceneObject *> refobjects = scene.candidates;
           
            if (refray.trace(refobjects))
            {
                RGBAPixel refColor = refray.shade(lights, refobjects, bgcolor, scene);
                r += (kr*refColor.red);
                g += (kr*refColor.green);
                b += (kr*refColor.blue);
            }
            else
            {
                r += (kr*bgcolor.red);
                g += (kr*bgcolor.green);
                b += (kr*bgcolor.blue);                   
            }
        }
    }

    int ir = min(255, (int) r);
    int ig = min(255, (int) g);
    int ib = min(255, (int) b);
    //std::cout << red << green << blue << std::endl;
    return RGBAPixel(ir, ig, ib);
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}
