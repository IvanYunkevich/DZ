// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;




 bool printArr(const double* arr, const size_t MS)
{
	for (size_t i = 0; i < MS; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return true;
}




int main()
{
	const size_t MS = 5;
	double arr[MS] = { 1.11, 2.22, 3.33, 4.44, 5.55 };
	if (printArr(arr, MS))
	{
		cout << "Array was successfully printed" << endl;
	}
    

	return 0;

}


