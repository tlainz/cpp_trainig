#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool cmp(int X, int Y){

    return X < Y;

}

int main()
{
    //index  0  1  2  3  4   5  6
    int A[]={1, 4, 2, 0, 5, 10, 9};

    //sort(first position, last position+1, comparaison function(optional))
    sort(A, A+7, cmp);

    for(int i=0;i<=6;++i){
        cout << A[i]<<" ";
    }
    return 0;
}
