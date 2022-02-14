// ConsoleApplicationTEST1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

void PrintArray(const int size, int* arr)
{

    for (int i = 0, j = 1; i < size; j += 3, ++i)
    {
        arr[i] = j;
        cout << j << " ";
    }
}
int main() 
{
    const int SIZE = 8;
    int arr[SIZE];
    PrintArray(SIZE, arr);
    return 0;
}