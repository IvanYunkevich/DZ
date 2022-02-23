
#include <iostream>
#include <fstream>

#include "MyLib.h"
using namespace std;

void task5()
{
	const int size = 4;
	const float* arr = MyLib::CreateInitArray(size);
	if (arr != nullptr)
	{
		MyLib::printArray(arr, size);
		MyLib::PrintNegativeAndPosNumbers(arr, size);
		delete[] arr;
	}

}

//=======================================================================================================================
#define INRANGE(x, y) ((x >= 0 && x < y) ? "True" : "False")
void task2()
{
    setlocale(LC_ALL, "Russian");
    int n;
	cout << "Введите число: " << endl;
    cin >> n;
    cout << INRANGE(n, 10) << endl;


}
#define SIZE_ARRAY 5

//========================================================================================================================
void task3()
{

	setlocale(LC_ALL, "Russian");
	int* arr = new (nothrow) int[SIZE_ARRAY];
	if (arr != nullptr)
	{
		cout << "Введите числа : " << endl;
		for (size_t i = 0; i < SIZE_ARRAY; i++)
		{
			cin >> arr[i];
		}
		cout << "Ваш массив: ";
		for (size_t i = 0; i < SIZE_ARRAY; i++)
		{
			cout << arr[i] << " ";
		}

		MyLib::SortingArr(arr, SIZE_ARRAY);
		delete[] arr;


	}


}


int main()
{
	//task1();
	//task2();
	task3();
	return 0;
}
