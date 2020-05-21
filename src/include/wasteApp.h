#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>

#include "user.h"
#include "MutablePriorityQueue.h"
#include "edge.h"
#include "../lib/graphviewer.h"

using namespace std;

class WasteApp {
    vector<User> users;
    vector<Vertex> vertexes;
    vector<Edge> edges;
    vector<Spot> spots;
    float xMin;
    float yMin;
    float xMax;
    float yMax;

public:
    WasteApp();

    vector<User> &getUsers();

    void setUsers(vector<User> &users);

    void addUser(User u);

    void addVertex(Vertex v);

    void addEdge(Edge e);

    bool hasVertex(int id);

    Vertex getVertex (int id);

    void generateGraph();

    int getXVertex(float x);

    int getYVertex(float y);

    Spot closestSpot(const User &u, float q, enum type type);
};


#endif //SRC_WASTEAPP_H
