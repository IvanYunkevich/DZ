#include <iostream>
using namespace std;

namespace MyLib
{

	void printArray(const float* array, size_t Arrsize) // Реализация функции (вывод массива на экран) //ConsoleApplicationtem.cpp
	{
		for (int i = 0; i < Arrsize; i++)
			cout << array[i] << " ";
	}
	float* CreateInitArray(const size_t size)
	{



		float* pArray = new (nothrow) float[size];
		if (pArray != nullptr)
		{
			for (size_t i = 0; i < size; i++)
			{
				pArray[i] = (rand() % 50) - 30.0f;
			}
		}


		return pArray;
	}


	void PrintNegativeAndPosNumbers(const float* arr, const size_t size)
	{
		setlocale(LC_ALL, "RUSSIAN");




		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] < 0)
			{
				cout << "\n" << "Отрицательное: " << arr[i];
			}
			else
			{
				cout << "\n" "Положительное: " << arr[i];

			}
		}

		/*size_t pos = 0U, neg = 0U;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] > 0.0f)
			{
				pos++;
			}
			else if (arr[i] < 0.0f)
			{
				neg++;
			}
		}*/


	}
#define SWAP_INT(x, y) int temp = x; x = y; y = temp;
	void SortingArr(int* arr, const size_t size)
	{

		for (int i = 1; i < size; ++i)
		{
			for (int r = 0; r < size - i; r++)
			{
				if (arr[r] < arr[r + 1])
				{
					/* Обмен местами
					int temp = arr[r];
					arr[r] = arr[r + 1];
					arr[r + 1] = temp;*/

					SWAP_INT(arr[r], arr[r + 1]);
				}
			}
		}
		cout << "Отсортированный массив: ";
		for (int i = 0; i < size; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
}