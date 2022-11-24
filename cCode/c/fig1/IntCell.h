
#ifndef IntCell_H
#define IntCell_H

class IntCell
{
private:
    int storedValue;
public:
    explicit IntCell(int initValue = 0);
    int read() const;
    void write(int x);
};

#endif