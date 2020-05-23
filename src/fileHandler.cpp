#include <cmath>
#include "fileHandler.h"

void readUserData(WasteApp &wasteApp, string userfilename){
    string username, password, vertex, position;
    enum userType type;
    ifstream userFile(userfilename);
    while(getline(userFile, username)){
        getline(userFile, password);
        getline(userFile, vertex);
        getline(userFile, position);
        if(position == "Client")
            type = CLIENT;
        else
            type = WORKER;
        wasteApp.addUser(User(username, password,stoi(vertex),type));
    }
}

void readRequestData(WasteApp &wasteapp){
    string username, type, quantity;
    auto tGlass = GLASS, tPaper = PAPER, tPlastic = PLASTIC, tOrganic = ORGANIC;
    ifstream requestFile("../data/requests.txt");
    while(getline(requestFile, username))
    {
        getline(requestFile, type);
        getline(requestFile, quantity);
        for(User &u : wasteapp.getUsers())
        {
            if(u.getUsername() == username)
            {
                vector<HouseRequest> r = u.getRequests();
                if (type == "Organic")       r.push_back(HouseRequest(tOrganic, stoi(quantity)));
                else if(type == "Glass")     r.push_back(HouseRequest(tGlass, stoi(quantity)));
                else if(type == "Paper")     r.push_back(HouseRequest(tPaper, stoi(quantity)));
                else if(type == "Plastic")   r.push_back(HouseRequest(tPlastic, stoi(quantity)));
                u.setRequests(r);
            }
        }
    }
}

void readSpotsData(WasteApp &wasteApp, string spotsfilename){
    string num_tag_string, tag, num_spots_string, vertex;
    int num_tags, num_spots;
    enum type tGlass = GLASS, tPaper = PAPER, tPlastic = PLASTIC, tOrganic = ORGANIC;
    ifstream spotFile(spotsfilename);
    getline(spotFile, num_tag_string);
    num_tags = stoi(num_tag_string);
    while (num_tags != 0) {
        num_tags--;
        getline(spotFile, tag);
        getline(spotFile, num_spots_string);
        num_spots = stoi(num_spots_string);
        if (tag.substr(0, 4) == "spot") {
            if (tag.substr(5, 5) == "glass") {
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    wasteApp.addSpot(Spot(tGlass,0,20,stoi(vertex)));
                }
            }
            if (tag.substr(5, 7) == "plastic") {
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    wasteApp.addSpot(Spot(tPlastic,0,20,stoi(vertex)));
                }
            }
            if (tag.substr(5, 5) == "paper") {
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    wasteApp.addSpot(Spot(tPaper,0,20,stoi(vertex)));
                }
            }
            if (tag.substr(5, 7) == "organic") {
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    wasteApp.addSpot(Spot(tOrganic,0,20,stoi(vertex)));
                }
            }
        } else if (tag.substr(0, 8) == "building") {
            if (tag.substr(9, 5) == "house") {
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    wasteApp.addHouse(House(stoi(vertex)));
                }
            }
            if (tag.substr(9, 7) == "central") {
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    wasteApp.addCentral(House(stoi(vertex)));
                }
            }
        }
    }
}

void readGraphData(WasteApp &wasteApp, const string &folder) {
    int n, id, v1, v2, c1, c2;
    float x, y;
    string temp;

    string filename = folder + "/nodes.txt";
    ifstream nodes (filename);

    if(nodes.is_open()) {
        getline(nodes, temp);
        n = stoi(temp);

        for (int i = 0; i < n; i++) {
            getline(nodes, temp);
            c1 = temp.find(',', 0);
            id = stoi(temp.substr(1, c1 - 1));
            c2 = temp.find(',', c1 + 1);

            x = stof(temp.substr(c1 + 1, c2 - c1 - 1));
            y = stof(temp.substr(c2 + 1, temp.length() - 1));
            wasteApp.addVertex(Vertex(id, x, y));
        }
        nodes.close();
    } else {
        cout << "Couldn't open nodes file!" << endl;
    }

    filename = folder + "/edges.txt";
    ifstream edges (filename);

    if(edges.is_open()) {
        getline(edges, temp);
        n = stoi(temp);

        for(int i = 0; i < n; i++) {
            getline(edges, temp);
            c1 = temp.find(',', 0);
            v1 = stoi(temp.substr(1, c1-1));
            v2 = stoi(temp.substr(c1 + 1, temp.length()-1));
            if (wasteApp.hasVertex(v1) && wasteApp.hasVertex(v2)) {
                wasteApp.addEdge(Edge(sqrt(pow((wasteApp.getVertex(v1).getX() - wasteApp.getVertex(v2).getX()),2) + pow((wasteApp.getVertex(v1).getY() - wasteApp.getVertex(v2).getY()),2)), i, v1, v2));
                wasteApp.addAdjacent(v1,i);
            }
            else cout << "Couldn't add edge: " << v1 << " -> " << v2 << endl;
        }
        edges.close();
    } else {
        cout << "Couldn't open edges file!" << endl;
    }
}

void updateRequests(WasteApp &wasteApp){
    string type;

    ofstream requestFile("../data/requests.txt");

    for(int j = 0; j < wasteApp.getUsers().size(); j++)
    {
        User u = wasteApp.getUsers()[j];
        vector<HouseRequest> r = u.getRequests();

        for(int i = 0; i < r.size(); i++)
        {
            if     (r[i].getType() == ORGANIC)  type = "Organic";
            else if(r[i].getType() == GLASS)    type = "Glass";
            else if(r[i].getType() == PAPER)    type = "Paper";
            else                                type = "Plastic";

            if(i != r.size()-1 || j != wasteApp.getUsers().size())
                requestFile << u.getUsername() << endl << type << endl << r[i].getQuantity() << endl;
            else
                requestFile << endl << u.getUsername() << endl << type << endl << r[i].getQuantity();
        }
    }
}
