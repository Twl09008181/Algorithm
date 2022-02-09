#include "graph.h"

graph::val graph::addVertex(val v){
    auto node = vertex.find(v);
    if(node==vertex.end()){
        node = vertex.insert(node,{v,adjList.size()});
        adjList.push_back({});
    }
    return node->second;
}
void graph::addEdge(val v1,val v2,weight w){
    val idx1 = addVertex(v1);
    val idx2 = addVertex(v2);
    adjList.at(idx1).push_back({v2,w});
    adjList.at(idx2).push_back({v1,w});
}
