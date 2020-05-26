#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>
#include <chrono>
#include <map>
#include <stack>

#include "user.h"
#include "spot.h"
#include "MutablePriorityQueue.h"
#include "edge.h"
#include "../lib/graphviewer.h"

using namespace std;

class WasteApp {

    vector<User> users;
    vector<Vertex> vertexes;
    map<int, Vertex*> vertexMap;
    vector<Edge> edges;
    vector<Spot> spots;
    vector<House> houses;
    vector<House> centrals;

    map<int, Vertex*> vertexesRevGraph;
    vector<Edge> edgesRevGraph;
    stack<Vertex*> vertexesRev;

    // USED IN GRAPHVIEWR
    float xMin;
    float yMin;
    float xMax;
    float yMax;
    float graphScale;

public:
    WasteApp();

    vector<User> &getUsers();

    void setUsers(vector<User> &users);

    void addAdjacent(int v, int e);

    void addUser(User u);

    void addVertex(Vertex* v);

    void addEdge(Edge e);

    void addSpot(Spot s);

    void addHouse(House h);

    void addCentral(House c);

    bool hasVertex(int id);

    Vertex* getVertex (int id);

    //Shows path from the client's house (green) to the closest spot (blue)
    void generateGraph(Vertex s);

    //Shows path from the worker's house (green) to the central (blue) passing through the houses (yellow)
    void generatePath(Vertex &next);

    Edge getEdge (int id);

    int getXVertex(float x, float s);

    int getYVertex(float y, float s);

    float getGraphScale() const;

    void setGraphScale(float g);

    const vector<House> &getHouses() const;

    //Returns the closest spot of the type provided that can fit the quantity
    Spot closestSpot(const User &u, float q, enum type type);

    //Dijkstra's algorithm beginning on vertex vID
    void dijkstra(const int &vID);

    Vertex* held_karp(const User &w, vector<Vertex *> housesToCollect);

    float g(Vertex *s, Vertex *v, vector<Vertex *> &path);

    void generatePath(Vertex* next);

    void fillOrder(Vertex *v, stack<Vertex*> &stack);

    void util(Vertex *v);


    int conectividade();
};


#endif //SRC_WASTEAPP_H
