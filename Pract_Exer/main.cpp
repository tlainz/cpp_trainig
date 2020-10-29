#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream f("data.in");

int Left, Right, X,n, operaciones;
int Array[100];

void add(int Left, int Right, int X){

    for (int i = Left; i<=Right; ++i){


        Array[i] = Array[i] + X;

    }

}
void valores(int operaciones){


    for(int j=1; j<=operaciones;++j){

    cout<<"\n Add (Left, Right, X): \n";
    cin>>Left>>Right>>X;
    if(Left>n || Right>n) {
            cout<<"Valores incorrectos";
            break;
            }
    add(Left, Right, X);
    }
    for(int i=1; i<=n; ++i){

        cout<<Array[i]<<" ";
    }

}
int main()
{
    f>>n; // number of elements

    for (int i=1; i<=n; ++i) {
    f>>Array[i];
    }
    cout<<"Cuantas operaciones hay?: \n";
    cin>>operaciones;
    valores(operaciones);
    return 0;
}
