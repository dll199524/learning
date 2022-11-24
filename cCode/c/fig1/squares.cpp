#include <iostream>
#include <vector>
using namespace std;




void swap(vector<string> & x, vector<string> & y)
{
    vector<string> temp = std::move(x);
    x = std::move(y);
    y = std::move(temp);
}


int main() 
{
    vector<int> squares(100);
    for (int i = 0; i < squares.size(); i++)
        squares[i] = i * i;
    for (int i = 0; i < squares.size(); i++)
        cout << i << " " << squares[i] << endl;

    return 0; 
    
}