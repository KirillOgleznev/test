#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>


#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void sum()
{
	int a = 10, b = -10;
	printf("%d", a + b);
}

void Menu();


int CHOICE();


void cleaning(int, char*);


void allocation(char *&);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	char *newstr = NULL;
	char *neword = NULL;
	char *fstr = NULL;


	int check = 0;
	int check1 = 0;
	int check2 = 0;
	int counter = 0;
	int length = 0;

	bool flag = false;


	while (!flag)
	{


		Menu();


		switch (CHOICE())
		{
		case 1:
			cleaning(check, newstr);
			cleaning(check, neword);
			cleaning(check, fstr);


			newstr = new char[1];
			newstr[0] = '\0';


			printf("Введите текст с которым нужно будет работать\n");
			scanf("%*c");
			allocation(newstr);


			neword = new char[1];
			neword[0] = '\0';


			printf("\nВведите слово: ");
			allocation(neword);


			fstr = new char[1];
			fstr[0] = '\0';


			printf("\n");


			check = 1;
			check1 = 0;
			check2 = 0;
			length = 0;


			break;


		case 2:
			if (check1)
			{
				printf("Текст уже был обработан.\n");
				break;
			}
			check2 = 1;


			counter = 0;
			if (check)
			{
				for (int i = 0; i < strlen(newstr); i++)
				{
					if (newstr[i] > 'А' - 1 && newstr[i] < 'Я' + 1) newstr[i] += 'а' - 'А';
				}


				if (strstr(newstr, neword) != NULL)
				{
					check1 = 1;
					for (int i = 0; i < strlen(newstr); i++)
					{
						counter++;
						if (newstr[i] == '.' || newstr[i] == '?' || newstr[i] == '!')
						{
							char *point1 = &newstr[i];
							char *point2 = NULL;
							int ch = 0;
							int p1 = point1 - newstr;
							int p2 = -1;
							while (p2 < p1)
							{
								point2 = strstr(newstr, neword);
								int word_length = strlen(neword);


								if (point2 != NULL)
								{
									p2 = point2 - newstr;
								}
								else
								{
									p2 = 32766;
								}


								if (p2 < p1)
								{
									if (p2 != 0)
									{
										if ((newstr[p2 - 1] == ' ') && (newstr[p2 + word_length] == ' ' || newstr[p2 + word_length] == '!' || newstr[p2 + word_length] == '?' || newstr[p2 + word_length] == '.'))
										{
											ch++;
										}
									}
									else if (newstr[p2 + word_length] == ' ' || newstr[p2 + word_length] == '!' || newstr[p2 + word_length] == '?' || newstr[p2 + word_length] == '.')
									{
										ch++;
									}


									if (ch == 1)
									{
										check2 = 0;
										length += counter;
										char *tmp = new char[length + 1];
										strcpy(tmp, fstr);
										strncat(tmp, point1 - counter + 1, counter);
										delete[] fstr;
										fstr = tmp;
									}
									newstr[p2] = '~';
								}
							}
							counter = 0;
						}
					}
				}


				for (int i = 0; i < strlen(fstr); i++)
				{
					if (fstr[i] == '~')
					{
						fstr[i] = neword[0];
					}
				}


				for (int i = 0; i < strlen(fstr); i++)
				{
					if (i == 0)
					{
						if (fstr[i] != ' ')
						{
							fstr[i] += 'А' - 'а';
						}
						else
						{
							fstr[i + 1] += 'А' - 'а';
						}
					}


					if (fstr[i] == '.' || fstr[i] == '?' || fstr[i] == '!')
					{
						if (i + 2 < strlen(fstr))
						{
							fstr[i + 2] += 'А' - 'а';
						}
					}
				}
				printf("Текст обработан.\n");
			}
			else
			{
				printf("Сначала нужно ввести текст и задать слово!\n");
			}
			break;


		case 3:
			if (check)
			{
				if (check2)
				{
					printf("В тексте нет данного слова\n");
				}
				else if (check1 && strlen(fstr))
				{
					if (fstr[0] == ' ')
					{
						puts(fstr + 1);
					}
					else puts(fstr);
				}
				else
				{
					puts(newstr);
				}
			}
			else
			{
				printf("Сначала нужно ввести текст и задать слово!\n");
			}
			break;


		case 4:
			flag = true;


			cleaning(check, newstr);
			cleaning(check, neword);
			cleaning(check, fstr);


			break;


		default:
			printf("\nДанные некорректны, повторите ввод\n\n");
		}
	}


	getchar();


	_CrtDumpMemoryLeaks();


	return 0;
}


void Menu()
{
	printf(" ____________________________________________________________________\n");
	printf("|                                                                    |\n");
	printf("|Выберите действие над текстом:                                      |\n");
	printf("|Введите цифру 1, чтобы произвести ввод текста и ключевого слова     |\n");
	printf("|Введите цифру 2, чтобы оставить предложения только с заданным словом|\n");
	printf("|Введите цифру 3, чтобы вывести текст на экран                       |\n");
	printf("|Введите цифру 4, чтобы выйти из программы                           |\n");
	printf("|____________________________________________________________________|\n");
}


int CHOICE()
{
	char digit[8];
	scanf("%s", &digit);
	return atoi(digit);
}


void cleaning(int check, char *news)
{
	if (check)
	{
		delete[] news;
	}
}


void allocation(char *&news)
{
	while (true)
	{
		char s = getchar();


		if (s == '\n')
		{
			break;
		}


		int len = strlen(news);
		char *tmp = new char[len + 2];
		strcpy(tmp, news);
		tmp[len] = s;
		tmp[len + 1] = '\0';
		delete[] news;
		news = tmp;
	}
}