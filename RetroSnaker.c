#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 50
#define HIGH 20

typedef struct Node {
	int x, y;
	struct Node* next;
}Snake;

int food[2];

Snake* head;
int g_direction = 1;//全局变量：蛇的方向 
int g_score = 0;
int sleeptime = 300;
int best_score; 

void gotoxy(int a, int b) { HANDLE hout;     COORD coord;     coord.X = a;     coord.Y = b;     hout = GetStdHandle(STD_OUTPUT_HANDLE);     SetConsoleCursorPosition(hout, coord); }
void Menu();
void InitSnake();
void PaintWall();
void MoveBody();
void ChangeDir();
void CreateFood();
int GetFood();
void PrintScore();
int TouchWall();
int BiteSelf();
int Dead();
void GameOver();
void LoadInfo();
void SaveInfo();

int main()
{
	Menu();
	getch();
	begin:
	LoadInfo();
	system("cls");
	PaintWall();
	InitSnake();
	CreateFood();
	PrintScore();
	while (1)
	{
		ChangeDir();
		MoveBody();
		if (Dead() == 1)
		{
			break;
		}
	}
	SaveInfo();
	GameOver();
	goto begin;
	return 0;
}

void LoadInfo()
{
	FILE* fp;
	fp = fopen("SnakeScore.txt","r");
	if (!fp)
	{
		printf("Please create \"SnakeScore.txt\" to save the game data!(⊙o⊙)？");
	}
	fscanf(fp, "%d", &best_score);
	fclose(fp);
}

void SaveInfo()
{
	FILE* fp;
	fp = fopen("SnakeScore.txt","w");
	fprintf(fp, "%d", best_score);
}

void Menu()
{
	gotoxy(5,HIGH/3);
	int i;
	for (i = 1; i <= WIDTH/2; i++)
	{
		printf("※");
	}
	printf("\n");
	gotoxy(5,HIGH*2/3);
	for (i = 1; i <= WIDTH/2; i++)
	{
		printf("※");
	}
	printf("\n");
	gotoxy(20,HIGH/2);
	printf("RETRO SNAKER");
	gotoxy(10,HIGH*3/5);
	printf("Please press any key to start the game");
}

void PaintWall()
{
	int i;
	for (i = 1; i <= WIDTH; i++)
	{
		printf("#");
	}
	for (i = 1; i <= HIGH; i++)
	{
		gotoxy(0, i);
		printf("#");
		gotoxy(WIDTH-1, i);
		printf("#");
	}
	gotoxy(0, HIGH);
	for (i = 1; i <= WIDTH; i++)
	{
		printf("#");
	}
}

//头插法初始化蛇身 
void InitSnake()
{
	g_direction = 1;//顺便初始化全局变量 
	g_score = 0;
	sleeptime = 300;
	head = (Snake*)malloc(sizeof(Snake));
	head->x = WIDTH / 2;
	head->y = HIGH / 2;
	head->next = NULL;
	gotoxy(head->x, head->y);
	printf("*");
	Snake* nexthead;
	int i;
	for (i = 0; i < 4; i++)
	{
		nexthead = (Snake*)malloc(sizeof(Snake));
		nexthead->x = head->x + 1;
		nexthead->y = head->y;
		nexthead->next = head;
		head = nexthead;
		gotoxy(head->x, head->y);
		printf("*");
	}
	
}

void MoveBody(){
	Snake* nexthead;//新的头 
	nexthead = (Snake*)malloc(sizeof(Snake));
	switch(g_direction)
	{
		case 1:
			nexthead->x = head->x;
			nexthead->y = head->y - 1;
			break;
		case 2:
			nexthead->x = head->x;
			nexthead->y = head->y + 1;
			break;
		case 3:
			nexthead->x = head->x - 1;
			nexthead->y = head->y;
			break;
		case 4:
			nexthead->x = head->x + 1;
			nexthead->y = head->y;
			break;
	}
	
	nexthead->next = head;
	head = nexthead;
	Snake* p = head;
	while (p->next->next != NULL)
	{
		gotoxy(p->x,p->y);
		printf("*");
		p = p->next;
	}
	gotoxy(p->x,p->y);
	printf("*");
	gotoxy(p->next->x,p->next->y);
	if ( GetFood()==1 ) 
	{
		Sleep(sleeptime);
		return;
	}
	printf(" ");//用空格掩盖蛇尾 
	free(p->next);//释放蛇尾 
	p->next = NULL;
	Sleep(sleeptime);
	
} 

void ChangeDir()
{
	if (kbhit())
	{
		char c;
		c = getch();
		switch(c)
		{
			case 'w':
				if (g_direction != 2)
				{
					g_direction = 1;
				} 
				
				break;
			case 's':
				if (g_direction != 1)
				g_direction = 2;
				break;
			case 'a':
				if (g_direction != 4)
				g_direction = 3;
				break;
			case 'd':
				if (g_direction != 3) 
				g_direction = 4;
				break;	
		}
	}
}

void CreateFood()
{
	srand((int)time(NULL));
	here:
	food[0] = rand() % (WIDTH-2) + 1;//保证食物不出现在墙里 
	food[1] = rand() % (HIGH-2) + 1;
	Snake* p = head;
	while (p != NULL)
	{
		if ( p->x==food[0] || p->y==food[1] )//如果蛇身坐标和食物坐标重复 
		{
			goto here;//重新生成食物 
		}
		p = p->next;
	}
	gotoxy(food[0],food[1]);
	printf("$");
}

int GetFood()
{
	if (head->x == food[0] && head->y == food[1])//如果吃到食物，即蛇头坐标等于食物坐标 
	{
		g_score ++;
		if (g_score > best_score)
		{
			best_score = g_score;
		}
		if (g_score >= 5)
		{
			sleeptime = 200;
		}
		else if (g_score >=10)
		{
			sleeptime = 100;
		}
		PrintScore();
		CreateFood();
		return 1;
	}
	else
	{
		return 0;
	}
}

void PrintScore()
{
	gotoxy(10,HIGH+2);
	printf("Your score is: %d\n", g_score);
	gotoxy(10,HIGH+4);
	printf("Your best score is: %d\n", best_score);
}

int TouchWall()
{
	if (head->x <= 0 || head->x >= WIDTH)
	{
		return 1;
	}
	if (head->y <= 0 || head->y >= HIGH)
	{
		return 1;
	}
	return 0;
}

int BiteSelf()
{
	Snake* q = head->next;
	while (q != NULL)
	{
		if (head->x == q->x && head->y == q->y)
		{
			return 1;
		}
		q = q->next;
	}
	return 0;
}

int Dead()
{
	if (TouchWall()==1 || BiteSelf()==1)
	{
		return 1;
	}
	return 0;
}

void GameOver()
{
	system("cls");
	gotoxy(5,HIGH/3);
	int i;
	for (i = 1; i <= WIDTH/2; i++)
	{
		printf("※");
	}
	printf("\n");
	gotoxy(5,HIGH*2/3);
	for (i = 1; i <= WIDTH/2; i++)
	{
		printf("※");
	}
	printf("\n");
	gotoxy(20,HIGH/2);
	printf("GAME OVER");
	gotoxy(15,HIGH*3/5);
	printf("play again: press Y     exit: press N");
	char c;
	c = getch();
	if (c == 'y' || c == 'Y')
	{
		return;
	}
	else if (c == 'n' || c == 'N')
	{
		exit(0);
	}
}
