#include <bits/stdc++.h>

using namespace std;

int main()
{

    int n;
    int counter=0;
    cin>>n;
    bool A[n+1];
    memset(A,0,sizeof(A));
    for(int i=2;i<n;i++)
    {

        if(A[i])
            continue;
        cout<<i<<" ";
        counter++;
        for(int j=i;j<=n;j+=i)
        {
            A[j]=1;

        }

    }


    return 0;
}
