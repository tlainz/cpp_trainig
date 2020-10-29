#include <iostream>
# include <bits/stdc++.h>

using namespace std;

struct item
{

    int value, weight;
    char name[10];

    item ()
    {
        value=0;
        weight=0;
        memset(name, 0, sizeof(name));
    }

}items[10];

bool cmp (item A, item B)
{
    return(1.0*A.value/A.weight) > (1.0*B.value/B.weight); // 1.0* de int a double
}
int main()
{
    int W = 7;
    int sum, imax, val, maxWeight=0, maxVal=0;
    char name1[]="Llaves", name2[]="Reloj", name3[]="Tablet", name4[]= "Movil";

    items[1].value=3;   items[1].weight=1;  strcpy(items[1].name, name1);
    items[2].value=3;   items[2].weight=2;  strcpy(items[2].name, name2);
    items[3].value=4;   items[3].weight=5;  strcpy(items[3].name, name3);
    items[4].value=7;   items[4].weight=6;  strcpy(items[4].name, name4);

    sort(items+1,items+5, cmp);

    for(int i=1; i<=4;++i)
    {
        sum = items[i].weight+items[i-1].weight;
        val = items[i].value+items[i-1].value;

        if (sum<= W && val > maxVal){ //&& sum >= maxWeight

        maxWeight= sum;
        maxVal = val;
        imax=i;
        }

    }
    cout<<"Se alcanzara el valor maximo con los items: "<<items[imax].name<<" y "<<items[imax-1].name<<"\n";

   /* item reloj;

    reloj.value=5; reloj.weight=3;
    item pulsera(8, 1);
*/
    return 0;
}
