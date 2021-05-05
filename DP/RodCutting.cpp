#include <vector>
#include <iostream>
#include <stack>




int Rod_Cutting(const std::vector<int>&P,std::vector<int>&Revenue,int n,std::vector<int>&record)
{
    if(n==0)
        return 0;

    if(Revenue[n-1] != 0)return Revenue[n-1];
    
    //遞迴式  Rn = max(Pi,Rn-i-1);
    //若n < p.size()
    //P有效index = 0 ~ n-1 ,i 設為0 ~ n-1
    //R有效index = 0 ~ n-1 ,代表 Rn-0-1,Rn-(n-1)-1

    int p_size = P.size();
    int q;

    //切割分成兩塊,一塊是長度i,一塊是長度n-i,可以切成1,n-1,2,n-2....... n,0 (一塊)
    for(int i = 1;i <= std::min(n,p_size) ;i++)//std::min(n,p_size):有效P的index
    {
        q = P[i-1] + Rod_Cutting(P,Revenue,n-i,record);
        if(q > Revenue[n-1])
        {
            Revenue[n-1] = q;
            record[n-1] = i;//切成長度為i以及n-i兩塊
        }
    }

    return Revenue[n-1];
}



int main()
{



    std::vector<int>P = {1,5,8,9,10,17,17,20,24,30};//Pi代表長度i+1的原收益
    
    int N ;
    std::cout<<"enter N\n";
    std::cin>>N;
    std::vector<int>Revenue(N);//Ri 代表長度為i+1之最大收益
    std::vector<int>record(N);//recordi代表長度為i+1時的最佳切點

    int R = Rod_Cutting(P,Revenue,N,record);
    std::cout<<"max Revenue = "<<R<<"\n";


    //印出切法
    //record[i]代表長度為i+1的切法

    std::cout<<"rods = \n";
    std::stack<int>S;
    S.push(N);
    while(!S.empty())
    {
        int L = S.top();S.pop();
        int cut = record[L-1];
        
        if(cut == L)//不用切
            std::cout<<L<<" ";
        
        else 
        {
            S.push(cut);//分成長度為cut
            S.push(L-cut);//以及長度為L-cut
        }
    }

    return 0;
}
