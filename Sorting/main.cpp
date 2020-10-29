#include <iostream>

using namespace std;

#define GetSize(array_enteros) (sizeof(array_enteros)/sizeof(*(array_enteros)))

int A[]={2,3,1,5,4,4};
int n = GetSize(A);

int sort_func(int A[]){

    for(int i=0;i<n;++i){
        for (int j=0;j<n;++j){

            if (A[i]<A[j]) swap (A[i], A[j]);
        }
    }
    return 0;
}

int main()
{
    sort_func(A);
    for(int i=0;i<n;++i){
    cout << A[i];
    }
    return 0;
}
