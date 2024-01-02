#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class Vertex {
public:
    string id;
    map<string, float> connectedTo;
    // Added for Breadth-First Algorithm
    char color;
    float dist;
    Vertex *pred;

    Vertex() {
        // w for white, g for grey, b for black
        color = 'w';
        dist = 0;
        pred = NULL;
    }

    Vertex(string key) {
        id = key;
        color = 'w';
        dist = 0;
        pred = NULL;
    }

    void addNeighbor(string nbr, float weight = 1) {
        connectedTo[nbr] = weight;
    }

    vector<string> getConnections() {
        vector<string> keys;
        // Use of iterator to find all keys
        for (map<string, float>::iterator it = connectedTo.begin();
             it != connectedTo.end();
             ++it) {
            keys.push_back(it->first);
        }
        return keys;
    }

    string getId() {
        return id;
    }

    float getWeight(string nbr) {
        return connectedTo[nbr];
    }

    friend ostream &operator<<(ostream &, Vertex &);
};

ostream &operator<<(ostream &stream, Vertex &vert) {
    vector<string> connects = vert.getConnections();
    stream << vert.id << " -> ";
    for (unsigned int i = 0; i < connects.size(); i++) {
        stream << connects[i] << endl << "\t";
    }

    return stream;
}

class Graph {
    public:
        map<string, Vertex> vertList;
        int numVertices;
        bool directional;

        Graph(bool directed = true) {
            directional = directed;
            numVertices = 0;
        }

        Vertex addVertex(string key) {
            numVertices++;
            Vertex newVertex = Vertex(key);
            this->vertList[key] = newVertex;
            return newVertex;
        }

        Vertex *getVertex(string n) {
            return &vertList[n];
        }

        bool contains(string n) {
            for (map<string, Vertex>::iterator it = vertList.begin();
                 it != vertList.end();
                 ++it) {
                if (it->first == n) {
                    return true;
                }
            }
            return false;
        }

        void addEdge(string f, string t, float cost = 1) {
            if (!this->contains(f)) {
                this->addVertex(f);
            }
            if (!this->contains(t)) {
                this->addVertex(t);
            }
            vertList[f].addNeighbor(t, cost);

            if (!directional) {
                vertList[t].addNeighbor(f, cost);
            }
        }

        vector<string> getVertices() {
            vector<string> verts;

            for (map<string, Vertex>::iterator it = vertList.begin();
                 it != vertList.end();
                 ++it) {
                verts.push_back(it->first);
            }
            return verts;
        }

        friend ostream &operator<<(ostream &, Graph &);
};

ostream &operator<<(ostream &stream, Graph &grph) {
    for (map<string, Vertex>::iterator it = grph.vertList.begin();
         it != grph.vertList.end();
         ++it) {
        stream << grph.vertList[it->first];
        cout << endl;
    }

    return stream;
}

string getBlank(string str, int index) {
    string blank = str;
    blank[index] = '_';
    return blank;
}

Graph buildGraph(vector<string> words) {
    Graph g(false);

    map<string, vector<string> > d;

    // Go through the words
    for (unsigned int i = 0; i < words.size(); i++) {
        // Go through each letter, making it blank
        for (unsigned int j = 0; j < words[i].length(); j++) {
            string bucket = getBlank(words[i], j);
            // Add the word to the map at the location of the blank
            d[bucket].push_back(words[i]);
        }
    }

    for (map<string, vector<string> >::iterator iter = d.begin();
         iter != d.end();
         ++iter) {
        for (unsigned int i = 0; i < iter->second.size(); i++) {
            for (unsigned int j = 0; j < iter->second.size(); j++) {
                if (iter->second[i] != iter->second[j]) {
                    g.addEdge(iter->second[i], iter->second[j]);
                }
            }
        }
    }

    return g;
}

Graph bfs(Graph g, Vertex *start) {
    start->dist = 0;
    start->pred = NULL;
    queue<Vertex *> vertQueue;
    vertQueue.push(start);
    while (vertQueue.size() > 0) {
        Vertex *currentVert = vertQueue.front();
        vertQueue.pop();
        for (unsigned int nbr = 0; nbr < currentVert->getConnections().size(); nbr++) {
            if (g.vertList[currentVert->getConnections()[nbr]].color == 'w') {
                g.vertList[currentVert->getConnections()[nbr]].color = 'g';

                g.vertList[currentVert->getConnections()[nbr]].dist =
                    currentVert->dist + 1;
                g.vertList[currentVert->getConnections()[nbr]].pred =
                    currentVert;
                vertQueue.push(&g.vertList[currentVert->getConnections()[nbr]]);
            }
        }
        currentVert->color = 'b';
    }

    return g;
}

void traverse(Vertex *y) {
    Vertex *x = y;

    while (x->pred) {
        cout << x->id << endl;
        x = x->pred;
    }
    cout << x->id << endl;
}

int main() {
    // Vector Initialized with an array
    string arr[] = {"fool",
                    "cool",
                    "pool",
                    "poll",
                    "pole",
                    "pall",
                    "fall",
                    "fail",
                    "foil",
                    "foul",
                    "pope",
                    "pale",
                    "sale",
                    "sage",
                    "page"};

    vector<string> words(arr, arr + (sizeof(arr) / sizeof(arr[0])));

    // Graph g = buildGraph(words);
    Graph g(false);

    g = buildGraph(words);

    g = bfs(g, g.getVertex("fool"));

    traverse(g.getVertex("pall"));

    return 0;
}
