#include <iostream>
#include "assert.h"


template <class E>
class Node
{
private:
    E e;
    Node * next;
public:
    Node(E e, Node * next) {
        this->e = e;
        this->next = next;
    }
    ~Node();
};


template <class E>
class LinkedList
{
private:
    Node * head = nullptr;
    int len;

public:

    int size();
    void push(E e);
    void insert(E e, int index)
    E remove(int index);
    Node<E> find(int index);

    LinkedList();
    ~LinkedList();
};

template <class E>
int LinkedList<E>::size() {
    return len;
}

template <class E>
Node<E> LinkedList<E>::find(int index) {
    assert(index > 0 && index < len);
    Node * temp = head;
    if (index < len << 1) {
        for (int i = 0; i < index; i++)
            temp = temp.next;
        
    } else if (index >= len >> 1) {
        for (int i = len; i > index; i--)
            temp = temp.next; 
    }
    return temp;
}





int main() {
    LinkedList list = new LinkedList();
}
