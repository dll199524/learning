#include "IntCell.h"
#include <iostream>
#include <vector>
using namespace std;

// ~IntCell();                                     //析构函数
// IntCell(const IntCell & rhs);                   //拷贝构造函数
// IntCell(IntCell && rhs);                        //移动构造函数
// IntCell & operator = (const IntCell & rhs);     //拷贝赋值
// IntCell && operator =(IntCell && rhs);          //移动赋值


IntCell::IntCell(int initValue) : storedValue{initValue}
{
}

int IntCell::read() const
{
    return storedValue;
}

void IntCell::write(int x)
{
    storedValue = x;
}

//函数模板
template <typename Comparable>
const Comparable & findMax(const vector<Comparable> & a)
{
    int maxIndex = 0;
    for (int i = 1; i < a.size(); i++)
        if(a[maxIndex] < a[i])
            maxIndex = i;
    return a[maxIndex];
}



//类模板
// template <typename Object>
// class MemoryCell
// {
//     public:
//         explicit MemoryCell(const Object & initValue = Object{})
//         : storedValue{initValue} {}
//         const Object & read() const
//         {return storedValue;}
//         void write(const Object & x)
//         {storedValue = x;}
//     private:
//     Object storedValue;
// }




int main()
{
    // IntCell m;
    // m.write(5);
    // cout << "Cell contents: " << m.read() << endl;

    IntCell *m;

    m = new IntCell{0};
    m->write(5);
    cout << "Cell contents: " << m->read() << endl;
    delete m;

    return 0;
}