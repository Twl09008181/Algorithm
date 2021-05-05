#include <iostream>
#include <vector>
#include <utility>




//dimension index : 0 .... n-1 n.
//M1's dimension = dimension[0] * dimension[1]
//Mi's dimension = dimension[i-1] * dimension[i]
std::pair<int,std::vector<std::vector<int>>> Matrix_Chain_Min(std::vector<int>dimension)
{
    int n = dimension.size() - 1;// n is Matrix number 

    std::vector<std::vector<int>>cost(n+1,std::vector<int>(n+1));
    std::vector<std::vector<int>>record(n+1,std::vector<int>(n+1));


    //init 
    for(int i = 1;i <= n;i++)cost[i][i] = 0;

    for(int length = 2;length <= n;length++)
    {
        for(int i = 1;i <= n - length + 1;i++)
        {
            int j = i + length -1;
            cost[i][j] = 1000000;//infinite
            for(int k = i;k < j;k++)
            {
                int C = cost[i][k] + cost[k+1][j] + dimension[i-1]*dimension[k]*dimension[j];
                if(C < cost[i][j])
                {
                    cost[i][j] = C;
                    record[i][j] = k;
                }
            }
            
        }

    }


    return {cost[1][n],record};
}



void show_result(std::vector<std::vector<int>>&Record,int l,int r)
{

    if(r==l)
    {
        std::cout<<"A"<<l;
        return ;
    } 

    int k = Record[l][r];
    


    std::cout<<"(";
    show_result(Record,l,k);

    show_result(Record,k+1,r);
    std::cout<<")";

}

int main()
{
    std::vector<int>D = {5,2,3,4,6,7,8};
    auto result = Matrix_Chain_Min(D);
    std::cout << result.first<<" ";


    //show result

    int n = D.size() - 1;//Matrix number

    show_result(result.second,1,n);



    return 0;
}
