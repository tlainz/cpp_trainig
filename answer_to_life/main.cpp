#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

ifstream f("input.in");
ofstream g("output.out");
int i=5;
int main()
{
    string datos;
    int salida = 42;

    while(getline(f,datos)){

    //   f>>datos[i];

        int iDatos = stoi(datos);
        if(iDatos==salida) return 0;
        g<<datos<<"\n";
       // i++;
     }
     f.close();
     g.close();
    return 0;
}
