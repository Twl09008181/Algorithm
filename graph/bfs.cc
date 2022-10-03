#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;


class graph{
public:
  int numNodes;
  vector<vector<int>>out;
  vector<vector<int>>in;
  graph(int n)
    :numNodes{n}

  {
    out.resize(n);
    in.resize(n);
  }
  void addEdge(int i, int j){
    out[i].push_back(j);
    in[j].push_back(i);
  }
};



void bfsTopDown(graph&G, int start){
  queue<int>frontier;
  frontier.push(start);
  vector<int>parent(G.numNodes, -1);
  parent[start] = start;
  while(!frontier.empty()){
    int v = frontier.front();frontier.pop();
    cout << v <<" ";
    for(int u:G.out[v]){
      if(parent[u] == -1){
        parent[u] = v;
        frontier.push(u);
      }
    }
  }
}



void bfsBottomUp(graph&G, int start){
  set<int>frontier;
  frontier.insert(start);
  vector<int>parent(G.numNodes, -1);
  parent[start] = start;

  int step = 0;
  while(!frontier.empty()){
    cout<<"step: "<<step++<<"\n";
    for(auto f:frontier){
      cout<<f<<" ";
    }
    cout<<"\n";
    set<int>nextFrontier;

    //search from child to parent
    for(int u = 0; u < G.numNodes; u++){
      if(parent[u] != -1)
        continue;
      for(int p:G.in[u]){
        auto isInFrontier = frontier.find(p);
        if(isInFrontier != frontier.end()){
          parent[u] = p;
          nextFrontier.insert(u);
          break;
        }
      }
    }
    frontier = std::move(nextFrontier);
  }
}

int main(){

  graph G(5);
  G.addEdge(0,1);
  G.addEdge(0,2);
  G.addEdge(1,2);
  G.addEdge(1,4);
  G.addEdge(2,3);

  cout<<"top down\n";
  bfsTopDown(G, 0);
  cout<<"bottom up\n";
  bfsBottomUp(G, 0);



  return 0;
}
