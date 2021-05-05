#include <iostream>
#include <vector>
#include <algorithm>


struct task{
    task(char n,int d,int p)
        :name{n},profit{p},deadline{d}{}
    char name;
    int profit;
    int deadline;
};

bool decreasing_profit(const task&t1,const task&t2)
{
    return t1.profit >= t2.profit;
}

int Find(int i,std::vector<int>&Disjoint_set)
{
    int root = i;
    while(Disjoint_set[root] !=root){//not root
        root = Disjoint_set[root];//find root index
    }
    return root;
}

void Union_set(int i,int j,std::vector<int>&Disjoint_set)
{
    if(j>=0){
        int root1 = Find(i,Disjoint_set);
        int root2 = Find(j,Disjoint_set);
        
        Disjoint_set[root1] = root2;
    }
}
void Max_Profit_Scheduling(std::vector<task>&Task,int deadline)
{

    std::sort(Task.begin(),Task.end(),decreasing_profit);//profit大到小排列

    std::vector<int>slot(deadline+1,-1);
    std::vector<int>Disjoint_set;
    Disjoint_set.resize(deadline+1);
    
    //init 
    for(int i = 0;i <= deadline;i++)
        Disjoint_set[i] = i;
    


    for(int t_i = 0;t_i < Task.size();t_i++)//O(n)
    {
        //find feasible task
        int d = Task[t_i].deadline;

        //Find()
        int root = Find(d,Disjoint_set);

        //0代表沒位置放了
        if(root != 0)slot[root] = t_i;
        
        //Union root,root-1
        Union_set(root,root-1,Disjoint_set);
    }


    for(int i = 0;i <= deadline;i++)
    {
        if(slot[i]!=-1)
            std::cout<<Task[slot[i]].name<<" ";
    }
    std::cout<<"\n";
}


int main()
{

    std::vector<task> Tasks1 = 
    {
        {'a',2,100},
        {'b',1,19},
        {'c',2,27},
        {'d',1,25},
        {'e',3,15}
    };

   Max_Profit_Scheduling(Tasks1,3);

    std::vector<task> Tasks2 = 
    {
        {'a',4,20},
        {'b',1,10},
        {'c',1,40},
        {'d',1,30}
    };
    Max_Profit_Scheduling(Tasks2,4);
  


    std::vector<task> Tasks3 = 
    {
        {'a',2,30},
        {'b',1,35},
        {'c',2,25},
        {'d',2,40}
    };
    Max_Profit_Scheduling(Tasks3,2);
  
    return 0;
}
