#include <iostream>
#include <vector>
#include <string>


std::vector<std::vector<int>> LCS(std::string &x,std::string &y)
{
    int m = x.size();
    int n = y.size();

    std::vector<std::vector<int>> DP(m+1,std::vector<int>(n+1));

    for(int i = 0;i <= m;i++)DP[i][0] = 0;
    
    for(int i = 0;i <= n;i++)DP[0][i] = 0;


    for(int i = 1;i <= m;i++)
    {
        for(int j = 1;j <=n;j++)
        {
            if(x.at(i-1)==y.at(j-1))
                DP[i][j] = DP[i-1][j-1] + 1;
            else 
                DP[i][j] = std::max(DP[i-1][j],DP[i][j-1]);
        }
    }

    return DP;

}



void show_result(std::vector<std::vector<int>>&DP,std::string &x,std::string &y ,int m,int n,std::string str="")
{
    if(m==0||n==0)
    {
        for(auto ptr = str.rbegin();ptr!=str.rend();ptr++)
            std::cout << *ptr;
        std::cout<<"\n";

    }
    else if(m!=0 && n!=0){

        if(x.at(m-1)==y.at(n-1))
        {
            show_result(DP,x,y,m-1,n-1,str+x.at(m-1));
        }
        else {
            if(DP[m][n]==DP[m-1][n])
                show_result(DP,x,y,m-1,n,str);

            if(DP[m][n]==DP[m][n-1])
                show_result(DP,x,y,m,n-1,str);
        }
    }
}


int main()
{

    std::string X = "ABCBDAB";
    std::string Y = "BDCABA";

    auto DP = LCS(X,Y);
    int m = X.size();
    int n = Y.size();

    show_result(DP,X,Y,m,n);
    return 0;
}
