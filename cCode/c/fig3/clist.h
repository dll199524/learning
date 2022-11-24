
typedef int ElementType;

#ifndef clist_h
#define clist_h

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
List makeEmpty(List L);
int isEmpty(List L);
int isLast(Position P, List L);
Position find(ElementType X, List L);
void Delete (ElementType X, List L);
Position findPrevious(ElementType X, List L);
void insert(ElementType X, List L, Position P); //插入到P之后
void deleteList(List L);
Position header(List L);
Position first(List L);
Position advance(Position P);
ElementType retrieve(Position P);

#endif
