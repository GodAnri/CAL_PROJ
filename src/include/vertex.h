#ifndef CAL_PROJ_VERTEXES_H
#define CAL_PROJ_VERTEXES_H

#include <vector>

using namespace std;

class Vertex {
    float distance;
    bool visited;
    vector<int> adjacent_IDs;
    float x;
    float y;
    int ID;

public:
    int queueIndex = 0; 		// required by MutablePriorityQueue4

    Vertex () {
        visited = false;
        distance = 0;
        ID = -1;
        x = -1;
        y = -1;
    }
    Vertex (int ID, float x, float y) : ID(ID), x(x), y(y) {
        distance = 0;
        visited = false;
    };

    void setDistance (float d);

    void setVisited(bool v);

    vector<int> getAdjacentIds();

    void addAdjacent(int id);

    int getID();
    bool getVisited();
    float getDistance();
    float getX();
    float getY();

    bool operator<(Vertex & vertex) const;
};

#endif //CAL_PROJ_VERTEXES_H
