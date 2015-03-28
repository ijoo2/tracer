#include "vector3.h"

using namespace std;

Vector3::Vector3()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    _mag = 0.0;
}

Vector3::Vector3(double i, double j, double k)
{
    x = i;
    y = j;
    z = k;
    _mag = sqrt(x*x + y*y + z*z);
}

double Vector3::dot(Vector3 const & other)
{
    return x*other.x + y*other.y + z*other.z;
}

Vector3 Vector3::cross(Vector3 const & other)
{
    return Vector3(y*other.z - other.y*z, -(x*other.z - other.x*z),
                   x*other.y - other.x*y);
}

Vector3 Vector3::add(Vector3 const & other)
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::subtract(Vector3 const & other)
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::scalev(double scalar)
{
    return Vector3(x*scalar, y*scalar, z*scalar);
}

void Vector3::scale(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void Vector3::normalize()
{
    if (_mag != 0.0)
    {
        scale(1.0/_mag);
        _mag = 1.0;
    }

}

//Rotates phi-degrees around the z-axis, rotates theta degrees
//around the x-axis.
void Vector3::rotate(double phi, double theta)
{
    phi *= PI/180.0;
    theta *= PI/180.0;
    x *= cos(phi)*sin(theta);
    y *= sin(phi)*sin(theta);
    z *= cos(theta);
}

void Vector3::print()
{
    cout << "(" << x << ", " << y << ", " << z << ") ";
}

Vector3 cross(Vector3 & a, Vector3 & b)
{
    return a.cross(b);
}

double dot(Vector3 & a, Vector3 & b)
{
    return a.dot(b);
}

double Vector3::operator[](int ind)
{
    if (ind == 0)
        return this->x;
    else if (ind == 1)
        return this->y;
    else
        return this->z;
}
