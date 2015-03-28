#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "polygon.h"
#include "surface.h"


class Mesh
{
    public:
        Mesh();
        Mesh(Vector3 const & off);
        void _load_mesh(const std::string filename);
        void _clear_polygons(std::vector<SceneObject *> & polygons);
        void _rotate_mesh(double phi, double theta);
        std::vector<SceneObject *> _create_polygons(Surface surf);

        std::vector<Vector3> vertices;
        std::vector< std::vector<int> > faces;
        Vector3 offset;
};