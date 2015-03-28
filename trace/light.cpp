#include "light.h"

Light::Light()
{
    _type = AMBIENT;
    color = RGBAPixel();
    dir = Vector3();
}

Light::Light(int type, RGBAPixel c)
{
    _type = type;
    color = c;
    dir = Vector3();
}

Light::Light(int type, RGBAPixel c, Vector3 v)
{
    _type = type;
    color = c;
    dir = v;
    if (_type == DIRECTIONAL)
        dir.normalize();
}
