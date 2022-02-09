#ifndef GRAPH_HPP 
#define GRAPH_HPP
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>
#include <iterator>

struct edge{
    using weightType = int;
    edge(std::size_t out,weightType w = 1)
    :u{out},weight{w}{}
    weightType weight;
    std::size_t u;
};
class graph{
public:
    using val = std::size_t;
    using weight = edge::weightType;
    void addEdge(val,val,weight w = 1);
    std::list<edge>& adj(val v){return adjList.at(v);}
    std::map<val,val> getVertex(){return vertex;}
private:
    val addVertex(val);
    std::map<val,val>vertex;
    std::vector<std::list<edge>>adjList;
};
#endif
