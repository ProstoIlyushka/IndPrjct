#include<locale.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
void Move(int bLevelSize, int* freePlace, int* position)
{
	int s = 0, levelSize;
	switch (bLevelSize)
	{
	case 72:levelSize = 8; break;
	case 90:levelSize = 9; break;
	case 120:levelSize = 11; break;
	case 156:levelSize = 12; break;
	default: levelSize = 15;
	}
	do
	{
		char key = _getch();
		if (key == 'w')
		{
			for (int i = 1; i <= freePlace[0] && s==0; i++) if (freePlace[i] == *position - levelSize - 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		if (key == 'a')
		{
			for (int i = 1; i <= freePlace[0] && s == 0; i++) if (freePlace[i] == *position - 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		if (key == 's')
		{
			for (int i = 1; i <= freePlace[0] && s == 0; i++) if (freePlace[i] == *position + levelSize + 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		if (key == 'd')
		{
			for (int i = 1; i <= freePlace[0] && s == 0; i++) if (freePlace[i] == *position + 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		
	} while (s==0);
	return;
}
int checkSpikes(int* spikes, int position)
{
	int s = 0;
	for (int i = 1; i <= spikes[0]; i++)if (position == spikes[i])s++;
	return s;
}
void ShowMap(char* levelElements, int levelSize, int levelNumber, int moves, int phase, int* spikes, int position, int finish)
{
	setlocale(LC_ALL, "Russian");
	system("cls");
	int t = 0;
	for (int i = 0; i < levelSize; i++)
	{
		if (levelElements[i] == 'O' || levelElements[i] == '\n')printf("%c", levelElements[i]);
		else
		{
			if (i == position)printf("+");
			else
			{
				if (i == finish)printf("X");
				else
				{
					if (phase % 3)for (int j = 1; j <= spikes[0]; j++)
					{
						if (i == spikes[j])
						{
							printf("*");
							t++;
						}
					}
					if (!t) printf(" ");
				}

			}
		}
		t = 0;
	}
	printf("Уровень: %d\nКоличество ходов: %d\n", levelNumber, moves);
	return;
}
int ReadLevel(int levelNumber, char* levelElements, int* freePlace, int* spikes, int* start, int* finish)
{
	FILE* file;
	int a, levelSize;
	switch (levelNumber)
	{
	case(1):a = fopen_s(&file, "Lvl1.txt", "rt"); levelSize = 72; break;
	case(2):a = fopen_s(&file, "Lvl2.txt", "rt"); levelSize = 90; break;
	case(3):a = fopen_s(&file, "Lvl3.txt", "rt"); levelSize = 120; break;
	case(4):a = fopen_s(&file, "Lvl4.txt", "rt"); levelSize = 156; break;
	default:a = fopen_s(&file, "Lvl5.txt", "rt"); levelSize = 240;
	}
	for (int i = 0; i < levelSize; i++)
	{
		fscanf_s(file, "%c", &levelElements[i]);
		if (levelElements[i] == ' ' || levelElements[i] == '*' || levelElements[i] == '+' || levelElements[i] == 'X')
		{

			freePlace[0]++;
			freePlace[freePlace[0]] = i;
			if (levelElements[i] == '*')
			{
				spikes[0]++;
				spikes[spikes[0]] = i;
			}
			if (levelElements[i] == '+')
			{
				*start = i;
			}
			if (levelElements[i] == 'X')
			{
				*finish = i;
			}
		}
	}
	fclose(file);
	return levelSize;
}
int PlayLevel(int levelNumber)
{
	char levelElements[250];
	int freePlace[150];
	int spikes[15];
	int position;
	int finish;
	int moves = 0;
	int phase = 1;
	freePlace[0] = 0;
	spikes[0] = 0;
	int levelSize = ReadLevel(levelNumber, levelElements, freePlace, spikes, &position, &finish);
	do
	{
		ShowMap(levelElements, levelSize, levelNumber, moves, phase, spikes, position, finish);
		Move(levelSize, freePlace, &position);
		phase++;
		moves++;
		if (position == finish)break;
		else
		{
			if (phase % 3) if (checkSpikes(spikes, position))moves = 0;
		}
	} while (moves > 0);
	return moves;
}
int OneLevel(int levelNumber)
{
	setlocale(LC_ALL, "Russian");
	int moves = PlayLevel(levelNumber);
	system("cls");
	if (moves) printf("Уровень пройден\nКоличество ходов: %d\n", moves);
	else printf("Вы проиграли\n");
	printf("Нажмите любую клавишу для продолжения\n");
	_getch();
	return moves;
}
void FullGame()
{
	int moves, tMoves = 0;
	for (int i = 1; i < 6; i++)
	{
		moves = OneLevel(i);
		if (moves)tMoves += moves;
		else break;
	}
	if (moves)
	{
		system("cls");
		printf("Игра пройдена\nКоличество ходов : % d\n", tMoves);
		printf("Нажмите любую клавишу для продолжения\n");
		_getch();
	}
}
void ShowRules()
{
	setlocale(LC_ALL, "Russian");
	system("cls");
	printf("Чтобы играть, выключите Caps Lock и используйте ENG раскладку клавиатуры\n");
	printf("Для передвижения используйте wasd\n");
	printf("Цель - добраться до выхода (X)\n");
	printf("Остерегайтесь шипов (*). Если вы на них на ступите, вы тут же проиграете\n");
	printf("Нажмите любую клавишу для продолжения\n");
	_getch();
	return;
}
void Menu()
{
	setlocale(LC_ALL, "Russian");
	char key;
	int s;
	system("cls");
	printf("Добро пожаловать в меню!\nЕсли хотите пройти все уровни сразу, нажмите 0\nЕсли хотите пройти конкретный уровень, нажмите на цифру,\n соответствующую номеру уровня (1-5)\n");
	printf("Чтобы посмотреть правила, нажмите Пробел");
	key = _getch();
	if (key == '0') FullGame();
	if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' )s = OneLevel(int(key) - 48);
	if (key == ' ')ShowRules();
	return;

}
int main()
{
	while(true)Menu();
	return 0;
}
