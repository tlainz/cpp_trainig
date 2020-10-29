#include <iostream>
#include <bits/stdc++.h>
/* 1 1 1 1 2 3 4 */
using namespace std;

#define GetSize(array_enteros) (sizeof(array_enteros)/sizeof(*(array_enteros)))
int BinarySearch(int A[], int n, int OK){
    int Left=0, Right=n-1, mid, X, result=-1;

    X =A[n/2];

    while (Left<=Right) {
        mid=(Left+Right)/2;

        if(X==A[mid]){
            result=mid;
            if (OK==1) Right=mid-1;   //first occurrence
            if (OK==2) Left=mid+1; //last occurrence
        }else if (X<A[mid]) Right=mid-1;
        else Left = mid+1;

    }

    return result;
}

int main()
{
    int A[] = {2,3,1,2,2,1,1,4,1,2,2,2,2,2};
    int n = GetSize(A);
    int L= (n/2)+1;
   cout<<"n:"<<n<<" L:"<<L<<"\n";

    sort(A, A+n);

    for(int i=0;i<=n-1;++i){
        cout << A[i]<<" ";
    }
    int First = BinarySearch(A, n, 1);
    int Last = BinarySearch(A, n, 2);

    int num_oc= Last - First +1;
    cout<<"\n"<<num_oc<<"\n";
    if (num_oc >= L) cout<<"Majority element= "<<A[L-1];
        else cout<<"No hay majority element";
    return 0;
}
