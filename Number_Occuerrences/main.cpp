#include <iostream>
/*
Caso particular de la búsqueda binaria
*/
using namespace std;

#define GetSize(array_enteros) (sizeof(array_enteros)/sizeof(*(array_enteros)))

int BinarySearch(int A[], int n, int X, int OK){
    int Left=0, Right=n-1, mid, result=-1;

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
    int A[] = {1,1,1,2,3,3,3,3,3,3,3,5,5,6,6,6,8,9,9};
    int length = GetSize(A);
    int X=5;
    int FirstOcc = BinarySearch(A, length,X,1);
    int LastOcc = BinarySearch(A,length, X,2);

    if (FirstOcc == -1) cout<<"The element is not in the array";
                else cout<<"The element appears "<<LastOcc-FirstOcc+1;


    return 0;
}
