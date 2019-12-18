#include<iostream>
#include<stdlib.h>
using namespace std;
#define N 7

bool _bigraph(int arr[][N],int start_point, int *color,int c = 0)
{
    color[start_point] = c%2;
    for(int i = 0 ; i <N ; i++)
    {
        if((arr[start_point][i] || arr[i][start_point] )&& i != start_point)
            {
            if(color[i]==color[start_point]){
                return false;
            }
            if(color[i]==-1)
            {
                if(!_bigraph(arr,i,color,c+1))
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool is_bipartite(int arr[][N])
{
    int *color = new int[N];
    for(int i = 0 ; i <N ; i++)
    {
        color[i] = -1;
    }
    for(int i = 0 ; i <N; i++)
    {
        if(color[i] == -1)
        {
            if(!_bigraph(arr,i,color))
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int arr[7][7]={0};
    arr[0][1]=arr[0][2]=arr[1][3]=arr[4][1]=arr[5][2]=arr[5][6]=arr[6][0]=arr[6][4]=1;
if(is_bipartite(arr))
    cout<<"It is a bipartite graph";
else
    cout<<"Not a bipartite graph";
}
