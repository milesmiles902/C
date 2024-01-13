#include <list>         //std::list
#include <utility>      //std::pair
#include <algorithm>    //std::find
#include <map>          //std::map
#include <iostream>     //std::cout

class DFSGraph{
    typedef std::pair<int, std::list<int>> vertex_t;
    typedef std::map<int, vertex_t> graph_t;
public:
    const bool directional;
    DFSGraph(bool directional) : directional(directional){}

    bool containsVertex(int id){
        return vertices.count(id);
    }

    std::list<int>& getVertexConnections(int id){
        return vertices[id].second;
    }

    void addVertex(int id){
        if(containsVertex(id)){
            vertices[id].second.clear();
        }else{
            vertices[id] = std::make_pair(id, std::list<int>());
        }
    }

    vertex_t& getVertex(int id){
        return vertices[id];
    }

    void addEdge(int fromID, int toID){
        if(!containsVertex(fromID))
            addVertex(fromID);

        if(!containsVertex(toID))
            addVertex(toID);

        getVertexConnections(fromID).push_back(toID);
        if(!directional)
            getVertexConnections(toID).push_back(fromID);
    }

    void dfs(){
        std::list<int> visitedList;

        for(auto& cur : vertices){
            if(std::find(visitedList.begin(), visitedList.end(), cur.first) == visitedList.end()){
                dfsvisit(visitedList, cur.second);
            }
        }
    }

    void dfsvisit(std::list<int>& visitedList, vertex_t& vertex){
        visitedList.push_back(vertex.first);

        std::cout << "Visited Vertex With ID#: " << vertex.first << std::endl;

        for(int neighborID : vertex.second){
            if(std::find(visitedList.begin(), visitedList.end(), neighborID) != visitedList.end()){
                dfsvisit(visitedList, getVertex(neighborID));
            }
        }
    }
private:
    graph_t vertices;
};

int main(int argc, char** argv){
    DFSGraph graph(true);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 5);

    graph.addEdge(3, 4);
    graph.addEdge(3, 2);

    graph.addEdge(1, 5);
    graph.addEdge(1, 2);

    graph.addEdge(5, 4);
    graph.addEdge(5, 3);

    graph.dfs();

    return 0;
}

