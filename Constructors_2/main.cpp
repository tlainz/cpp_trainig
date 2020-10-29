#include <iostream>
# include <bits/stdc++.h>

using namespace std;

struct Product
{
    double Price;
    char Name[20];

    Product () //constructor
    {
        Price=0;
        memset(Name, 0, sizeof(Name));
    }
    Product (double newPrice)
    {
        Price=newPrice;
    }
    Product (int newPrice) //diferentes tipos de argumentos int, double...
    {
        Price = newPrice;
    }
    Product(char newName[], double newPrize)
    {
        Price=newPrize;
        memset(Name, 0, sizeof(Name));
        strcpy(Name, newName);
    }

};

int main()
{
    Product abc;
    abc.Price=5;
    char newName[]="Test";

    strcpy(abc.Name, newName);

    Product X(5.5);

    Product Y(2);

    Product Z("Apple", 2.5);
    cout<<X.Price<<" "<<Y.Price<<"\n";
    cout<<Z.Name<<" "<<Z.Price;
    return 0;
}
