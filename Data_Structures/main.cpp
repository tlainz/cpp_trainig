#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
struct [structure tag]
{
    member definition;
    member definition;
    ...
    member definition;
} [one or more structure variables](optional);
*/

struct books
{
    char Title[20];
    char Author[20];
    int ID;
    float price;
}book1;                 //global variable

struct car
{
    char model[20];
    int year;
    int ID;
}mycar, cars[1000];

void printingBooks(books variableBook){

    cout<<"Title: "<<variableBook.Title<<"\n";
    cout<<"Author: "<<variableBook.Author<<"\n";
    cout<<"ID: "<<variableBook.ID<<"\n";
    cout<<"Price: "<<variableBook.price<<"\n\n";

}


void printingCar (car variableCar) {
    cout<<variableCar.model<<" "<<variableCar.year<<"\n";
    cout<<variableCar.ID<<"\n";
    cout<<"\n";
}

int main()
{
    book1.ID=10;
    book1.price=13.99;
    strcpy(book1.Title, "Data Structures");
    strcpy(book1.Author, "Antonio Lainz");

/*
    cout<<"Title: "<<book1.Title<<"\n";
    cout<<"Author: "<<book1.Author<<"\n";
    cout<<"ID: "<<book1.ID<<"\n";
    cout<<"Price: "<<book1.price<<"\n\n";
*/
    books book2;
    book2.ID=20;
    book2.price=18.99;
    strcpy(book2.Title, "Data Structures 2");
    strcpy(book2.Author, "Antonio Lainz");

    printingBooks(book1);
    printingBooks(book2);

    ////////////////// CARS /////////////////
    strcpy(mycar.model, "Fast and furious");
    mycar.year=2017;

    cout<<mycar.model[0]<<mycar.model[1]<<mycar.model[2];
    cout<<mycar.model[3]<<"\n";

    for (int i=1; i<=100; ++i) {
        cars[i].ID=i;
        strcpy(cars[i].model, "Fast and furious");
        cars[i].year=2017;
    }

    // print cars[13] and cars[37]
    printingCar(cars[13]);
    printingCar(cars[37]);


    return 0;
}
