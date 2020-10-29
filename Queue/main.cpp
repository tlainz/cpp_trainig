#include <iostream>
#include <bits/stdc++.h>

/*Queue: Push(x), pop(), isEmpty() Front()
FIFO: First In First Out
backInd=-1
forntInd=0
*/
using namespace std;

int backInd = -1;
int frontInd = 0;
int Queue[100];
void Push(int x){
    ++backInd;
    Queue[backInd] = x;
}
void Pop(){
    Queue[frontInd] = 0;
    ++frontInd;
}
bool isEmpty(){
    if (backInd < frontInd) return true;
    else return false;
}
int Front(){
    return Queue[frontInd];
}

int main()
{
    Push(3);
    Push(4);
    cout<<Front();
    Pop();
    cout<<Front();
    Push(7);
    Push(8);
    cout<<Front();
    cout<<isEmpty();

    return 0;
}
