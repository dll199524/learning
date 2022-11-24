#ifdef VECTOR_H
#define VECTOR_H

template <typename Object>
class Vector
{
    //析构函数
    //拷贝构造函数
    //移动构造函数
    //拷贝赋值
    //移动赋值
public:
    explicit Vector(int initSize = 0)
        : theSize{initSize}, theCapacity{initSize + SPACE_CAPACITY}, {objects = new Object[theCapacity]};
    Vector(const Vector &rhs)
        : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}
    {
        objects = new Obejct[theCapacity];
        for (int i = 0; i < theSize; i++)
            objects[i] = rhs.objects[i];
    }
    Vector & operator=(const Vector &rhs)
    {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~Vector() { delete[] objects; }

    Vector(Vector &&rhs)
        : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector &operator=(Vector &rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);
    }

    bool isEmpty() const
    {return size() == 0;}

    int size() const
    {return theSize;}

    int capacity() const
    {return theCapacity;}

    Object & operator[] (int index)
    {
        if (index < 0 && index >= size())
            throw ArrayIndexOutOfBoundsException{};
        return objects[index];
    }

    const Object & operator[] (int index) const
    {
        if (index < 0 && index >= size())
            throw ArrayIndexOutOfBoundsException{};
        return objects[index];
    }

    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize*2);
        theSize = newSize;
    }

    void reserve(int newCapacity)
    {   
        if (newCapacity < theSize)
            return;
        Object * newArray = new Object[newCapacity];
        for (int i = 0; i < theSize; i++)
            newArray[i] = std::move(objects[i])
        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete [] newArray;        
    }

    void push_back(const Object & x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void push_back(Object && x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1)；
        objects[theSize++] = std::move(x);
    }

    void pop_back()
    {
        if (isEmpty())
            throw UnderflowException{};
        theSize--;  
    }

    const Object & back() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return objects[theSize--];
    }

    iterator begin()
    {return &objects[0];}

    const iterator begin() const
    {return &objects[0];}

    iterator end()
    {return &objects[theSize];}

    const iterator end() const
    {return &objects[theSize];}

    static const int SPACE_CAPACITY = 2;

private:
    int theSize;
    int theCapacity;
    Object *objects;
}

#endif VECTOR_H