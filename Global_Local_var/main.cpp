#include <iostream>

using namespace std;

int Aglobal[3];
int a;

void Printing()
{
    cout<<a<<"\n";

    int a=8; //primero imprimira la variable a global, luego la local
    cout<<a<<"\n";
}
int main()
{
   int Alocal[3];
   //cout<<"Aglobal is: "<<Aglobal[0]<<" "<<Aglobal[1]<<" "<<Aglobal[2]<<"\n";
   //cout<<"Alocal is: "<<Alocal[0]<<" "<<Alocal[1]<<" "<<Alocal[2]<<"\n";
    a=5;
    Printing();
    return 0;
}
