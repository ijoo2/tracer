#include "mesh.h"

using namespace std;

Mesh::Mesh()
{
    offset = Vector3();
}

Mesh::Mesh(Vector3 const & off)
{
    offset = off;
}

void Mesh::_load_mesh(const string filename)
{
    ifstream in(filename.c_str(), ios::in);
    if (!in)
    {
        cout << "Cannot open " << filename << endl;
        exit(1);
    }

    string line;

    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            Vector3 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            vertices.push_back(v);
        }

        else if (line.substr(0,2) == "f ")
        {
            istringstream s(line.substr(2));
            vector<int> poly;
            int ind;
            while (s >> ind)
            {
                ind--;
                poly.push_back(ind);
            }
            
            faces.push_back(poly);
        }

        else if (line[0] == '#') {}

        else {}

    }
}

vector<SceneObject *> Mesh::_create_polygons(Surface surf)
{
    vector<SceneObject *> polygons;
    for each (const auto &face in faces)
    {
        vector<Vector3> polyverts;
        //cout << "Face :";
        for each (const auto &ind in face)
        {
            //cout << "v" << ind << " ";
            //vertices[ind].print();
            polyverts.push_back(vertices[ind].add(offset));
        }

        //cout << endl;

        SceneObject * polygon = new Polygon(polyverts, surf);
        polygons.push_back(polygon);
    }
    return polygons;
}

void Mesh::_clear_polygons(vector<SceneObject *> & polygons)
{
    for (int i = 0; i < polygons.size(); i++)
    {
        delete polygons[i];
    }

    polygons.clear();
}

void Mesh::_rotate_mesh(double phi, double theta)
{
    for (int i=0; i < vertices.size(); i++)
    {
        Vector3 * vert = &vertices[i];
        vert->rotate(phi, theta);

    }
}