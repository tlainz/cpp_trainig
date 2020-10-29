#include <iostream>
#include <bits/stdc++.h>
/*Rancho is in love with Pihu. So on the Valentine’s Day they decided to spend time together at Assi Ghat,
but Rancho, as we all know is very busy with his work, so he failed. It was now Pihu’s turn to go mad with
anger. But there’s something which you can do.

Rancho tells Pihu that he is a novice programmer and is generally busy in solving problems at spoj. So Pihu
decides to check his algorithmic skills. She puts forward an array of N integers. She gives him a number P
and asks if he can find three (strictly three) integers Ai Aj Ak  ( i ≠ j ≠ k ) in the array, whose sum is
equal to number P, i.e.

Ai + Aj + Ak  =P.

Now, sooner Rancho answers her query in YES or NO, sooner he gets a kiss.

****Input****
The first line of input consists of an integer T, number of test cases.

The second line of input consists of an integer N, denoting the size of array.

The third line consists of N integers A1, A2 A3 ……………. AN , separated with space .

The fourth line consists of number P.

CONSTRAINTS

1<=T<=15

3<= N <= 1000

1<= Ai <= 10^9    where 1<= i <=N

1<= P <= 3*10^9

****Output****
If you find three numbers Ai ,Aj ,Ak  ,  ( i ≠ j ≠ k )  in the array such that Ai + Aj + Ak  =P, print “YES” else print “NO” ( quotes for clarification only).*/

using namespace std;
int ok, T, n;
long long P, A[1000];

int BinarySearch(int Left, int Right, long long X)
{
    int mid;
    while(Left<=Right){
        mid = (Left+Right)/2;
        if (A[mid]==X) return 1;
        else if (A[mid]>X) Right=mid-1;
        else Left=mid+1;
    }
    return -1;
}

int main()
{
    cin>>T;
    for (int t=1; t<=T;++t){

        cin>>n;

        for(int i=1;i<=n;++i) cin>>A[i];

        cin>>P;
        sort(A+1, A+n+1);

        ok=0;
        for(int i=1;i<n;++i)
        for(int j=i+1;j<=n;++j){
            long long auxSum= P-A[i]-A[j];

             if (BinarySearch(j+1,n, auxSum)==1) ok=1;
        }
        if(ok==1) cout<<"YES \n";
        else cout<<"NO\n";
    }
    return 0;
}
