#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
using namespace std;
enum TCell : char
{
	CROSS = 'X',//Состояния клеток
	ZERO = '0',
	EMPTY = '_'

};
//========================================================================================================================================
enum TProgress
{
	IN_PROGRESS,// Прогресс нашей игры
	WON_AI,
	WON_PLAYER,
	DRAW
};
//========================================================================================================================================
struct TCoord
{
	size_t y{ 0 };// Координаты
	size_t x{ 0 };
};
//========================================================================================================================================
struct TGame
{
	const size_t SIZE{ 3 }; //3 x 3
	TCell** ppFiled{ nullptr }; // наше игровое поле
	TCell ai;
	TCell player;
	TProgress progress{ IN_PROGRESS };
	size_t turn{ 0 }; // чей ход? четные числа это ход человека
};
//========================================================================================================================================
inline void clearScr()
{
	system("cls");
	//cout << "\x1B[2J\x1B[H";

}
//========================================================================================================================================
int32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}
//========================================================================================================================================
void __fastcall initGame(TGame& g)
{
	g.ppFiled = new TCell * [g.SIZE]; // Выделяем
	for (size_t i = 0; i < g.SIZE; i++)
	{
		g.ppFiled[i] = new TCell[g.SIZE];
	}

	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.ppFiled[y][x] = EMPTY;
		}
	}
	if (getRandomNum(0, 1000) > 500)
	{
		g.player = CROSS;
		g.ai = ZERO;
		g.turn = 0;
	}
	else
	{
		g.player = ZERO;
		g.ai = CROSS;
		g.turn = 1;
	}
}
//========================================================================================================================================
void __fastcall deinitGame(TGame& g)
{

	for (size_t i = 0; i < g.SIZE; i++) // Освобождаем выделенную память
	{
	 delete[] g.ppFiled[i];
	}
	delete[] g.ppFiled;
	g.ppFiled = nullptr;
}
//========================================================================================================================================
void __fastcall printGame(const TGame& g)
{
	setlocale(LC_ALL, "RUSSIAN");
	cout << "    ";
	for (size_t x = 0; x < g.SIZE; x++)
	{
		cout << x + 1 << "   ";
	}
	cout << endl;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		cout << "" << y + 1 << " | ";
		for (size_t x = 0; x < g.SIZE; x++)
		{
			cout << g.ppFiled[y][x] << " | ";
		}
		cout << endl;
	}

	cout << endl << " Игрок : " << g.player << endl << " Компьютер : " << g.ai << endl;

}
//========================================================================================================================================
TProgress __fastcall getWon(const TGame& g)
{
	//есть ли выйгрыш в строках?
	for (size_t y = 0; y < g.SIZE; y++)
	{
		if (g.ppFiled[y][0] == g.ppFiled[y][1] && g.ppFiled[y][0] == g.ppFiled[y][2])
		{
			if (g.ppFiled[y][0] == g.player)
				return WON_PLAYER;

			if (g.ppFiled[y][0] == g.ai)
				return WON_AI;
		}
	}
	//есть ли выйгрыш в столбцах?
	for (size_t x = 0; x < g.SIZE; x++)
	{
		if (g.ppFiled[0][x] == g.ppFiled[1][x] && g.ppFiled[0][x] == g.ppFiled[2][x])
		{
			if (g.ppFiled[0][x] == g.player)
				return WON_PLAYER;

			if (g.ppFiled[0][x] == g.ai)
				return WON_AI;
		}
	}
	//Диагонали
	if (g.ppFiled[0][0] == g.ppFiled[1][1] && g.ppFiled[0][0] == g.ppFiled[2][2])
	{
		if (g.ppFiled[0][0] == g.player)
			return WON_PLAYER;

		if (g.ppFiled[0][0] == g.ai)
			return WON_AI;
	}
	if (g.ppFiled[2][0] == g.ppFiled[1][1] && g.ppFiled[1][1] == g.ppFiled[0][2])
	{
		if (g.ppFiled[1][1] == g.player)
			return WON_PLAYER;

		if (g.ppFiled[1][1] == g.ai)
			return WON_AI;
	}
	//ничья
	bool draw{ true };
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppFiled[y][x] == EMPTY) //если хотя бы одна клетка пустая,значит ничья не наступила.
			{
				draw = false;
				break;
			}
		}
		if (!draw)
			break;
	}

	if (draw)
		return DRAW;

	return IN_PROGRESS;
}
//========================================================================================================================================
TCoord __fastcall getHumanCoord(const TGame& g)
{

	TCoord c{ 0 };
	do
	{
		setlocale(LC_ALL, "RUSSIAN");
		cout << "Введите X(1-3): ";
		cin >> c.x;
		cout << "Введите Y(1-3) : ";
		cin >> c.y;
		c.x--;
		c.y--;
	} while (c.x > 2 || c.y > 2 || g.ppFiled[c.y][c.x] != EMPTY);
	
	return c;
}
//========================================================================================================================================
TCoord __fastcall getComputerCoord(TGame& g)
{
	//PRE WIN SITUATION - поиск предвыйгранных ситуаций
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppFiled[y][x] == EMPTY)
			{
				g.ppFiled[y][x] = g.ai;
				if (getWon(g) == WON_AI)
				{
					g.ppFiled[y][x] == EMPTY;
					return { y, x };
				}
				g.ppFiled[y][x] = EMPTY;
			}
		}
	}
	//PRE FAIL SITUATION - поиск предпроигрышных ситуаций, чтобы помешать человеку
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppFiled[y][x] == EMPTY)
			{
				g.ppFiled[y][x] = g.player;
				if (getWon(g) == WON_PLAYER)
				{
					g.ppFiled[y][x] == EMPTY;
					return { y, x };
				}
				g.ppFiled[y][x] = EMPTY;
			}
		}
	}
	//1. Ход по приоритетам + 2. ранд

	//центр
	if (g.ppFiled[1][1] == EMPTY)
	{
		return { 1, 1 };

	}
	//углы
	TCoord buf[4];
	size_t num = 0;
	if (g.ppFiled[0][0] == EMPTY) // этот угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 0, 0 };
		num++;
	}
	if (g.ppFiled[2][2] == EMPTY) // этот угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 2, 2 };
		num++;
	}
	if (g.ppFiled[2][0] == EMPTY) // этот угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 2, 0 };
		num++;
	}
	if (g.ppFiled[0][2] == EMPTY) // этот угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 0, 2 };
		num++;
	}
	if (num > 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return buf[index]; // Возвращаем случайный угол из пустых
	}
	//не углы
	num = 0;
	if (g.ppFiled[0][1] == EMPTY) // этот не угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 0, 1 };
		num++;
	}
	if (g.ppFiled[2][1] == EMPTY) // этот не угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 2, 1 };
		num++;
	}
	if (g.ppFiled[1][0] == EMPTY) // этот не угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 1, 0 };
		num++;
	}
	if (g.ppFiled[1][2] == EMPTY) // этот не угол пустой?
	{
		//сохраним его, если да
		buf[num] = { 1, 2 };
		num++;
	}
	if (num > 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return buf[index]; // Возвращаем случайный не угол из пустых
	}
}
//========================================================================================================================================
void congrats(const TGame& g)
{
	setlocale(LC_ALL, "RUSSIAN");
	if (g.progress == WON_PLAYER)
	{
		cout << " Вы победили ! " << " ^_^ " << endl; //его вообще можно выйграть =) ?
	}
	else if (g.progress == WON_AI)
	{
		cout << " Победил компьютер " << " o_O " << endl;
	}
	else if (g.progress == DRAW)
	{
		cout << " Ничья " << " (-_-) " << endl;
	}
}
//========================================================================================================================================
int main()
{
	TGame g;
	initGame(g);
	clearScr();
	printGame(g);

	do
	{
		if (g.turn % 2 == 0)
		{
			TCoord c = getHumanCoord(g);//ход игрока
			g.ppFiled[c.y][c.x] = g.player;
		}
		else
		{
			TCoord c = getComputerCoord(g);//ход компьютера
			g.ppFiled[c.y][c.x] = g.ai;
		}

		g.turn++;
		clearScr();
		printGame(g);
		g.progress = getWon(g); // Не выйграл ли кто-то или ничья?
	} while (g.progress == IN_PROGRESS);

	congrats(g); // Поздравление

	deinitGame(g);

	return 0;
}

