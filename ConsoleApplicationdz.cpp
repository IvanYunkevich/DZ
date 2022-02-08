// ConsoleApplicationdz.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
void task1()
{
    int a, b;
    cout << "Enter a number a:";
    cin >> a;
    cout << "Enter a number b:";
    cin >> b;
    //cout << (a + b >= 10 && a + b <= 20) ? 100 : 200;
    if (a + b >= 10 && a + b <= 20)
        cout << "True";
    else
        cout << "False";

    
 
}
void task2()
{
    const int M = 5;
    const int N = 3;
    int c;
    if (M, N == 10 || M + N == 10)
        cout << "True";
    else
        cout << "False";


}
void task3()
{

    for (int i = 1; i <= 50; i += 2)
        cout << " Your number: " << i << " ";

}
int main()
{
    task3();
  
  
}


