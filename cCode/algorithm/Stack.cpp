#include <iostream>
#include "assert.h"
using namespace std;

template <class E>
class Stack
{
private:
    /* data */
    int size;
    int top = -1;

public:
    bool isEmpty();
    void push(E e);
    E pop(); 
    Stack(/* args */);
    ~Stack();
};


