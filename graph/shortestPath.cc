#include<iostream>
#include<vector>
#include <utility>
#include <queue>
#include <iomanip>
#include <time.h>
using namespace std;


enum class dir{
  NONE = 0,
  LEFT,
  RIGHT,
  TOP,
  DOWN
};

struct point{
  point(int x, int y, float cost, float hcost)
    :_x{x}, _y{y}, _cost{cost}, _heuristic{hcost}{}
  int _x, _y;
  float _cost;
  float _heuristic;
};


char obstk = 'o';


// if heuristic = true, then a* search
// otherwise, use dijkstra
void dijkstra(
    const vector<vector<int>>&maze,
    int sx, 
    int sy,
    int ex,
    int ey,
    bool heuristic){

  int row = maze.size();
  int col = maze.at(0).size();
  vector<vector<float>>bestCost(col, vector<float>(row, INT_MAX));



  auto cmp = [heuristic] (const point&lhs, const point&rhs){
    if(heuristic)
     return lhs._cost + lhs._heuristic > rhs._cost + rhs._heuristic;
    else
     return lhs._cost > rhs._cost;
  };

  priority_queue<point, vector<point>,decltype(cmp)>pq(cmp);


  //show path required
  vector<vector<dir>>from(col, vector<dir>(row, dir::NONE));
  vector<vector<bool>>searched(col, vector<bool>(row, false));

  //initial
  bestCost[sx][sy] = 0;
  searched[sx][sy] = true;
  pq.push({sx,sy,0,0});


  auto getNeighbor = [row, col](int x, int y){ 
    vector< pair<pair<int,int>, dir> >neighbors;
    if(x > 0)
      neighbors.push_back({{x-1,y}, dir::RIGHT});
    if(x + 1 < col)
      neighbors.push_back({{x+1,y}, dir::LEFT});
    if(y > 0)
      neighbors.push_back({{x,y-1}, dir::TOP});
    if(y + 1 < row)
      neighbors.push_back({{x,y+1}, dir::DOWN});
    return neighbors;
  };


  while(!pq.empty()){

    point v = pq.top(); pq.pop();
    int x = v._x;
    int y = v._y;

    float cost = v._cost;
    searched[x][y] = true;

    // lazy remove
    if(cost > bestCost[x][y])
      continue;

    // find target
    if(x==ex && y==ey){
      break;
    }

    auto neighbor = getNeighbor(x, y);
    for(auto p:neighbor){
      auto coor = p.first;
      int ux = coor.first;
      int uy = coor.second;

      float heuristicCost = abs(ex-ux) + abs(ey-uy);
      float realCost = cost + maze[y][x];

      if(realCost < bestCost[ux][uy]){ 
        //relax
        bestCost[ux][uy] = realCost;
        pq.push({ux, uy, realCost, heuristicCost});
        from[ux][uy] = p.second;//update direction
      }
    }
  }



  cout<<"show path\n";

  // find path
  int x = ex;
  int y = ey;
  vector<vector<float>>findPath(col, vector<float>(row, -1));
  while(from[x][y] != dir::NONE){
    findPath[x][y] = bestCost[x][y];
    switch (from[x][y]){
      case dir::LEFT:
        x -= 1;
        break;
      case dir::RIGHT:
        x += 1;
        break;
      case dir::DOWN:
        y -= 1;
        break;
      case dir::TOP:
        y += 1;
        break;
    }
  }

  int searchPoint = 0;
  findPath[sx][sy] = 0;
  for(int y = 0; y < row; y++){
    for(int x = 0; x < col; x++){
      cout << setw(5);
      if(searched[x][y]){
        searchPoint++;
        if(findPath[x][y]==-1){
          cout<<'*';
        }else{
          cout<<findPath[x][y];
        }
      }
      else{
        cout<<'-';
      }
    }
    cout<<"\n";
  }
  cout<<"total search point"<<searchPoint<<"\n";

}



int main(int argc, char*argv[]){

  srand(time(0));

  int row = stoi(argv[1]);
  int col = stoi(argv[2]);
  int sx = stoi(argv[3]);
  int sy = stoi(argv[4]);
  int ex = stoi(argv[5]);
  int ey = stoi(argv[6]);
  vector<vector<int>>maze(row, vector<int>(col));

  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      maze[i][j] = rand()%10;
    }
  }

  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      cout << setw(5);
      cout<<maze[i][j];
    }
    cout<<"\n";
  }

  cout<<"dijkstra\n";
  dijkstra(maze,sx,sy,ex,ey,false);
  cout<<"a*\n";
  dijkstra(maze,sx,sy,ex,ey,true);

  return 0;
}
