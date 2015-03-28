#include "mesh.h"

using namespace std;

int _main()
{
    Mesh mesh = Mesh();
    mesh._load_mesh("mesh.obj");
    
    for (int i = 0; i < mesh.faces.size(); i++)
    {
        for (int j = 0; j < mesh.faces[i].size(); j++)
        {
            cout << mesh.faces[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}