#include<iostream>
#include<conio.h>
using namespace std;

#define middle "\n\n\n\n\n\n\n\n\n\n"
#define center "\t\t\t\t\t\t\t"

enum Delimiter:char
{
	vert_line = (char)179,
	horiz_line = (char)196,
	cross = (char)197
};

void ASCII()
{
	for (int i = 0; i < 224; i++)
	{
		cout << i << "\t" << (char)i << endl;
	}
}
void Init(char Field[], const int n);
void PrintField(char Field[], const int n, char Player);
void Move(char Field[], const int n, char Player);
void Check(char Field[], const int n, char Player);

void main()
{
	const int n = 9;
	char Field[n] = {};
	//PrintField(Field, n, '0');
	Init(Field, n);
	setlocale(LC_ALL, "");
	cout << "Еще разочек? (Yes/No):";
	setlocale(LC_ALL, "C");
	if (getch() == 121)main();
	//cout << (char)Delimiter::cross << endl;
	//ASCII();
}

void Init(char Field[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		Field[i] = 0;
	}
	PrintField(Field, n, '0');
}

void PrintField(char Field[], const int n, char Player)
{
	system("CLS");
	//setlocale(LC_ALL, "C");
	cout << middle;
	for (int i = 6; i >= 0; i -= 3)
	{
		//cout << center;
		cout.width(50);
		for (int j = 0; j < 3; j++)
		{
			cout << " " << Field[i + j] << " ";
			if (j != 2)cout << (char)vert_line;
		}
		cout << endl;
		if (i == 0)break;
		cout.width(50);
		cout << (char)horiz_line << (char)horiz_line << (char)horiz_line;
		cout << (char)cross;
		cout << (char)horiz_line << (char)horiz_line << (char)horiz_line;
		cout << (char)cross;
		cout << (char)horiz_line << (char)horiz_line << (char)horiz_line;
		cout << endl;
	}
	Check(Field, n, Player);
}

void Move(char Field[], const int n, char Player)
{
	char key;
	bool miss;	//промах
	bool busy;	//клетка занята
	do
	{
		do
		{
			miss = false;
			key = getch();
			if (key == 27)return;
			if (key < '1' || key > '9')
			{
				setlocale(LC_ALL, "Rus");
				cout << "Error: нажимай внимательней на кнопки!" << endl;
				setlocale(LC_ALL, "C");
				miss = true;
			}
		} while (miss);
		busy = false;	//предаоложим, что пользователь ходит в пустую клетку.
		if (Field[key - '1'] == 0)
		{
			Field[key - 49] = Player;
		}
		else
		{
			setlocale(LC_ALL, "Rus");
			cout << "Error: Клетка уже занята." << endl;
			setlocale(LC_ALL, "C");
			busy = true;
		}
	} while (busy);
	/*if(Player == 'X')PrintField(Field, n, '0');
	else PrintField(Field, n, 'X');*/
	PrintField(Field, n, Player);
}

void Check(char Field[], const int n, char Player)
{
	bool game_over = false;
	if (Field[0] == Field[4] && Field[4] == Field[8] && Field[0] != 0) game_over = true;
	else if (Field[2] == Field[4] && Field[4] == Field[6] && Field[6] != 0)game_over = true;
	else if (Field[0] == Field[1] && Field[1] == Field[2] && Field[2] != 0)game_over = true;
	else if (Field[3] == Field[4] && Field[4] == Field[5] && Field[5] != 0)game_over = true;
	else if (Field[6] == Field[7] && Field[7] == Field[8] && Field[8] != 0)game_over = true;
	else if (Field[0] == Field[3] && Field[3] == Field[6] && Field[6] != 0)game_over = true;
	else if (Field[1] == Field[4] && Field[4] == Field[7] && Field[7] != 0)game_over = true;
	else if (Field[2] == Field[5] && Field[5] == Field[8] && Field[8] != 0)game_over = true;
	if (game_over)
	{
		cout << Player << " wins" << endl;
		return;
	}
	bool draw = true;	//Предполагаем, что у нас ничья, но это нужно проверить.
	for (int i = 0; i < n; i++)
	{
		if (Field[i] == 0)draw = false;	//Если есть хотябы одна свободная клетка, то игра продолжается.
	}
	if (draw)
	{
		cout << "Draw" << endl;
		return;
	}
	if (Player == 'X')Move(Field, n, '0');
	else Move(Field, n, 'X');
}
