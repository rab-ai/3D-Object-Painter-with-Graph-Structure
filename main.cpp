#include "BinaryHeap.h"
#include "MeshGraph.h"
#include "ObjLoader.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argv, const char* argc[])
{
    string object_name = argc[1];
    char third_argument;
    if (object_name == "plane.obj" or object_name == "plane-low.obj") {
        third_argument = 'q';
    }
    else if (object_name == "plane-low2.obj" or object_name == "facem-low2.obj") {
        third_argument = 't';
    }
    else {
        cerr << "Invalid object name" << endl;
        return 1;
    }
    ObjLoader loader;
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    string working_directory = cwd;
    Color color = {0, 29, 250};
    loader.LoadObjFile(working_directory + "/" + object_name);
    vector<IdPair> edges = loader.GetEdges();
    vector<Double3> vertices = loader.GetVertexPos();
    vector<Color> colors;
    MeshGraph graph(vertices, edges);
    graph.PaintInRangeEuclidian(colors, 5, color, 8, FILTER_BOX, 5);
    graph.WriteColorToFile(colors, "color.txt");
    string command = "./CENG-213-OBJ-Loader " + object_name + " color.txt " + third_argument;
    system(command.c_str());
    return 0;
}