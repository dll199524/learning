#include <list>
#include <vector>
#include <iostream>
using namespace std;


template <typename Container>
void removeEveryOtherItem(Container & lst)
{
    auto itr = lst.begin();
    while (itr != lst.end())
    {
        itr = lst.erase(itr);
        if (itr != lst.end())
            ++itr;
    }
    
}

template <typename Container>
void print(const Container &c, ostream & out = cout)
{
    if (c.empty())
        out << "(empty)";
    else
    {
        auto itr = begin(c);
        out << "[" << *itr++;
        while (itr != end(c))
            out << "," << *itr++;
        out << "]" << endl;
        
    }
}


int main() 
{
    list<int> list;
    for (int i = 0; i < 9; i++)
        list.push_back(i);
    removeEveryOtherItem(list);
    print(list, cout);
    
}