#include "clist.h"
#include <stdlib.h>
#include <stdio.h>

struct Node
{
    ElementType element;
    Position next;
};

List makeEmpty(List L)
{
    if (L != NULL)
        deleteList(L);
    L = (struct Node *)malloc(sizeof(struct Node));
    if (L == NULL)
        printf("out of memory");
    L->next == NULL;
    return L;
}

int isEmpty(List L) { return L->next == NULL; }

int isLast(Position P, List L) { return P->next == NULL; }

Position find(ElementType X, List L)
{
    Position P;
    P = L->next;
    while (P != NULL && P->element != X)
        P = P->next;
    return P;
}

void Delete(ElementType X, List L)
{
    Position P, temp;
    P = findPrevious(X, L);
    if (!isLast(P, L))
    {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }
}

Position findPrevious(ElementType X, List L)
{
    Position P;
    P = L;
    while (P->next != NULL && P->next->element != X)
        P = P->next;
    return P;
}

void insert(ElementType X, List L, Position P)
{
    Position temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    if (temp == NULL)
        printf("out of space");
    temp->element = X;
    temp->next = P->next;
    P->next = temp;
}

void deleteList(List L)
{
    Position P, temp;
    P = L->next;
    L->next = NULL;
    while (P != NULL)
    {
        temp = P->next;
        free(P);
        P = temp;
    }
}

Position header(List L) { return L; }

Position first(List L) { return L->next; }

Position advance(Position P) { return P->next; }

ElementType retrieve(Position P) { return P->element; }

void printList(const List L)
{
    Position P = header(L);
    if (isEmpty(L))
        printf("empty list");
    else
    {
        do
        {
            P = advance(P);
            printf("%d", retrieve(P));
        } while (!isLast(P, L));
        printf("\n");
    }
}

int main()
{
    List L;
    Position P;
    int i;
    L = makeEmpty(NULL);
    P = header(L);
    printList(L);
    for (i = 0; i < 10; i++)
    {
        insert(i, L, P);
        printList(L);
        P = advance(P);
    }
    for (i = 0; i < 10; i += 2)
        Delete(i, L);

    printList(L);
    deleteList(L);

    return 0;
}
