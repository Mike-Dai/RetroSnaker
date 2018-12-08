#include <stdio.h>
#include <string.h>
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


void gotoxy(int a, int b) { HANDLE hout;     COORD coord;     coord.X = a;     coord.Y = b;     hout = GetStdHandle(STD_OUTPUT_HANDLE);     SetConsoleCursorPosition(hout, coord); }
void InitSnake();
void PaintWall();
void MoveBody();
void ChangeDir();
void CreateFood();
int GetFood();
void PrintScore();
int TouchWall();
int BiteSelf();
int GameOver();

int main()
{
	
	PaintWall();
	InitSnake();
	CreateFood();
	PrintScore();
	while (1)
	{
		
		/*if ( BiteFood() )
		{
		AddScore();
		AddSnake();
		AddFood();
		}
		if ( BiteSelf() )
		{
		GameOver();
		}*/
		ChangeDir();
		MoveBody();
		if (GameOver() == 1)
		{
			system("cls");
			printf("GAME OVER\n");
			break;
		}
	}
	
	return 0;
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
	gotoxy(0, HIGH-1);
	for (i = 1; i <= WIDTH; i++)
	{
		printf("#");
	}
}

//头插法初始化蛇身 
void InitSnake()
{
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
		Sleep(500);
		return;
	}
	printf(" ");//用空格掩盖蛇尾 
	free(p->next);//释放蛇尾 
	p->next = NULL;
	Sleep(300);
	
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
				g_direction = 1;
				break;
			case 's':
				g_direction = 2;
				break;
			case 'a':
				g_direction = 3;
				break;
			case 'd':
				g_direction = 4;
				break;	
		}
	}
}

void CreateFood()
{
	srand((int)time(NULL));
	here:
	food[0] = rand() % WIDTH + 1;
	food[1] = rand() % HIGH + 1;
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
	gotoxy(10,HIGH+5);
	printf("Your score is: %d\n", g_score);
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

int GameOver()
{
	if (TouchWall()==1 || BiteSelf()==1)
	{
		return 1;
	}
	return 0;
}
