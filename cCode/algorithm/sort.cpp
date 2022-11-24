#include <iostream>
using namespace std;

template <class T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
    
}

//选择最小的角标
template <class T>
void selectSort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
                min = j;
        }
        std::swap(arr[i], arr[min]);
        
    }
    
}

//插入到对应位置
template <class T>
void insertSort(T arr[], int size) {
    int j;
    for (int i = 1; i < size; i++)
    {
        int temp = arr[i];
        for (j = i; j > 0 && temp < arr[j - 1]; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
    
}


void print_arr(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout<<arr[i]<<endl;  
}



int main() {
    int arr[] = {1, 19, 4, 22, 55};
    // bubbleSort(arr, 5);
    // selectSort(arr, 5);
    insertSort(arr, 5);
    print_arr(arr, 5);
    return 0;
}

