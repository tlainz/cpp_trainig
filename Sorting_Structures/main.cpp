#include <iostream>
# include <bits/stdc++.h>

using namespace std;

struct Car
{
    int speed, price;

}cars[100];

bool cmp (Car A, Car B)
{
   /* if (A.speed!=B.speed)   return A.speed > B.speed;
    else return A.price < B.price;*/
    return(1.0*A.speed/A.price) > (1.0*B.speed/B.price); // 1.0* de int a double
}
int main()
{
    cars[1].speed = 100; cars[1].price=1200;
    cars[2].speed = 200; cars[2].price=1400;
    cars[3].speed = 200; cars[3].price=1600;
    cars[4].speed = 130; cars[4].price=1250;
    cars[5].speed = 150; cars[5].price=1400;
    cars[6].speed = 95; cars[6].price=1000;

    sort(cars+1, cars+7, cmp);

    return 0;
}
