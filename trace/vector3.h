#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>

#define PI 3.141592653

class Vector3
{
    public:
        Vector3();
        Vector3(double i, double j, double k);
        
        double dot(Vector3 const & other);
        Vector3 cross(Vector3 const & other);
        Vector3 add(Vector3 const & other);
        Vector3 subtract(Vector3 const & other);
        Vector3 scalev(double scalar);
        double operator[](int ind);
        void scale(double scalar);
        void normalize();
        void rotate(double phi, double theta);
        void print();

        double x, y, z, _mag;

};

Vector3 cross(Vector3 & a, Vector3 & b);
double dot(Vector3 & a, Vector3 & b);


#endif