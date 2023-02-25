#include<locale.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
void Move(int levelSize, int* freePlace, int* position)
{
	char key = _getch();
	int s = 0;
	do
	{
		if (key == 'w')
		{
			for (int i = 1; i <= freePlace[0]; i++) if (freePlace[i] == *position - levelSize - 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		if (key == 'a')
		{
			for (int i = 1; i <= freePlace[0]; i++) if (freePlace[i] == *position - 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		if (key == 's')
		{
			for (int i = 1; i <= freePlace[0]; i++) if (freePlace[i] == *position + levelSize + 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
		if (key == 'd')
		{
			for (int i = 1; i <= freePlace[0]; i++) if (freePlace[i] == *position + 1)
			{
				*position = freePlace[i];
				s++;
			}
		}
	} while (s);
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
	for (int i = 0; i < (levelSize + 1) * levelSize; i++)
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
					if (phase % 3)for (int j = 1; j <= spikes[0]; j++)if (i == spikes[j])printf("*");
					else printf(" ");
				}

			}
		}
		printf("Уровень: %d\nКоличество ходов: %d", levelNumber);
		return;
	}
}
int ReadLevel(int levelNumber, char* levelElements, int* freePlace, int* spikes, int* start, int* finish)
{
	FILE* file;
	int a;
	switch (levelNumber)
	{
	case(1):a = fopen_s(&file, "Lvl1/txt", "rt"); break;
	case(2):a = fopen_s(&file, "Lvl2/txt", "rt"); break;
	case(3):a = fopen_s(&file, "Lvl3/txt", "rt"); break;
	case(4):a = fopen_s(&file, "Lvl4/txt", "rt"); break;
	default:a = fopen_s(&file, "Lvl5/txt", "rt");
	}
	int levelSize = -1;
	do
	{
		levelSize++;
		fscanf_s(file, "%c", levelElements[levelSize]);
	} while (levelElements[levelSize] != '\n');
	for (int i = 1; i < levelSize; i++)
	{
		for (int j = 0; j <= levelSize; j++)
		{
			fscanf_s(file, "%c", levelElements[(levelSize + 1) * i + j]);
		}
	}
	fclose(file);
	for (int i = 0; i < levelSize; i++)
	{
		for (int j = 0; j <= levelSize; j++)
		{
			if (levelElements[(levelSize + 1) * i + j] == ' ' || levelElements[(levelSize + 1) * i + j] == '*' || levelElements[(levelSize + 1) * i + j] == '+' || levelElements[(levelSize + 1) * i + j] == 'X')
			{

				freePlace[0]++;
				freePlace[freePlace[0]] = (levelSize + 1) * i + j;
				if (levelElements[(levelSize + 1) * i + j] == '*')
				{
					spikes[0]++;
					spikes[spikes[0]] = (levelSize + 1) * i + j;
				}
				if (levelElements[(levelSize + 1) * i + j] == '+')
				{
					*start = (levelSize + 1) * i + j;
				}
				if (levelElements[(levelSize + 1) * i + j] == 'X')
				{
					*finish = (levelSize + 1) * i + j;
				}
			}
		}
	}
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
	int levelSize = ReadLevel(levelNumber, levelElements, freePlace, spikes, &position, &finish);
	while (moves > 0)
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
	}
	return moves;
}
int OneLevel(int levelNumber)
{
	setlocale(LC_ALL, "Russian");
	int moves = PlayLevel(levelNumber);
	system("cls");
	if (moves) printf("Уровень пройден\nКоличество ходов: %d", moves);
	else printf("Вы проиграли");
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
	if (moves)printf("Игра пройдена\nКоличество ходов : % d", tMoves);
}
void Menu()
{
	char key;
	int s;
	do
	{
		key = _getch();
		if (key == '0') FullGame();
		else s = OneLevel(int(key) - 48);
	} while (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5');

}
int main()
{
	Menu();
	return 0;
}