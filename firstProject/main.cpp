#include <iostream>
#include <bits/stdc++.h>

using namespace std;
ifstream f("data.in");
ofstream g("data.out");
int other(int c, int d, int maximum);
int main()
{
    int a, b,sum, maxi;

    f>>a>>b;
    sum=a+b;
    g<<sum;
    other(a,b,maxi);
    return 0;
}
int other(int a, int b, int maximum)
{
//    int a=5, b=8, maximum;
    // maximum from a and b
    maximum=max(a, b);
    printf("a=%d y b=%d\n",a,b);
    cout<<maximum<<"\n";
    //swapping two values
    swap(a, b); // a=8, b=5
    printf("a=%d y b=%d\n",a,b);
    //double pow (double base, double exponent);

    int number=2;
    double cubicRoot;

    cubicRoot=pow((double)(number), 1.0/3); // 1(or 3) is of type int / 1.0(or 3.0) is of type double

    cout<<fixed<<setprecision(10)<<cubicRoot<<"\n";
    cout<<fixed<<setprecision(3)<<cubicRoot<<"\n";

    return 0;
}
