#include <iostream>
#include <bits/stdc++.h>


 //LIFO: Last in First Out

using namespace std;

int Stack[100], ind;
char input[100];


void push (int x){

    ++ind;
    Stack[ind] = x;

}

bool isEmpty(){
    if (ind>=1) return false;
        else return true;

}
void pop(){
    Stack[ind] = 0;
    --ind;
}

int top(){
    return Stack[ind];
}

bool verify (char input[]){

    ind = 0;
    int n = strlen(input);

    for(int i=0; i<n; i++){

        if (input[i] == '(') push(1);
        if (input[i] == '[') push(2);
        if (input[i] == '{') push(3);

        if (input[i] == ')'){
            if (isEmpty() || Stack[ind] != 1) return false;
            else {
                Stack[ind]=0;
                --ind;
            }
        }
        if (input[i] == ']'){
            if (isEmpty() || Stack[ind] != 2) return false;
            else {
                Stack[ind]=0;
                --ind;
            }
        }
        if (input[i] == '}'){
            if (isEmpty() || Stack[ind] != 3) return false;
            else {
                Stack[ind]=0;
                --ind;
            }
        }
    }
    if(ind == 0) return true; //Si el stack esta vacio es que todo está bien
    else return false;
}
int main()
{
   cin>>input;

   if (verify(input)){
   cout<<"Correcto";
   } else cout<<"Incorrecto";

   return 0;
}
