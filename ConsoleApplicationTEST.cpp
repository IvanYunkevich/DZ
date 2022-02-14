

#include <iostream>
using namespace std;
void invertArray(const int size, int* arr) 
{
    cout << " ";
   
    for (int i = 0; i < size; ++i) 
    {
        cout << arr[i] << " ";
        arr[i] = !arr[i];
    }
   
    cout << endl;
   
    cout << " ";
   
    for (int j = 0; j < size; ++j) 
    {
        cout << arr[j] << " ";
    }
}

int main()
{
    const int MK = 5;
   
    int arr[MK];
    
    for (int& i : arr) i = rand() % 2;
    
    invertArray(MK, arr);
   
    return 0;
}
