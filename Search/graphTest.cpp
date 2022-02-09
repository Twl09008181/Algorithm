#include "graph.h"
#include <iostream>
int main(){
    graph gp;
    gp.addEdge(1,2,3);
    gp.addEdge(1,3);
    gp.addEdge(4,5);
    gp.addEdge(1,4,7);
    gp.addEdge(4,2);
    for(auto v:gp.getVertex()){
        std::cout<<v.first<<" :\n";
        for(auto &adj:gp.adj(v.second)){
            std::cout<<adj.u<<" "<<"weight:"<<adj.weight<<"\n";
        }
    }
    return 0;
}
