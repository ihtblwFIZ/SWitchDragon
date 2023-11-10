#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "block.h"
#pragma warning(disable:4996)

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

typedef struct Moogi
{
	struct Moogi* left;
	struct Moogi* right;
	COORD position;
}Moogi;

int** gameBoardInfo;
int direction = 0;
int stage = -1;
int stageBestScore[5];
int speed = 20;
int shield = 0;
int fever[5] = { 0,0,0,0,0 };
Moogi* head;
Moogi* tail;

void SetCurrentCursorPos(int x, int y) {}

void inStartScreenKeyInput();
int inPlayKeyInput();
void shiftUp();
void shiftDown();
void shiftLeft();
void shiftRight();
int pausePlay();
void goToStartScreen();
int detectCollision(int currentPosX, int currentPosY);
COORD nextHeadPos();
void drawHead(COORD headPos);
void eraseTail();
Moogi* getNode(Moogi* left, Moogi* right, COORD position);

int main()
{

	return 0;
}

void inStartScreenKeyInput()
{
	int i, key;

	for (i = 0; i < 20; i++)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			default:
				break;
			}
		}

		Sleep(speed);
	}
}

int inPlayKeyInput() // �÷��� ���� Ű �Է�
// �̹��� ���� �� �Ͻ�����
{
	int i, key, isDone = 0;

	for (i = 0; i < 20; i++)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			case UP:
				shiftUp();
				break;
			case DOWN:
				shiftDown();
				break;
			case LEFT:
				shiftLeft();
				break;
			case RIGHT:
				shiftRight();
				break;
			case SPACE:
				isDone = pausePlay();
				break;
			default:
				break;
			}
		}

		Sleep(speed); // �÷��� �ӵ� ����
	}

	return isDone;
}

void shiftUp() // �÷��� �� up ����Ű �Է� ��
{
	// �浹 Ȯ��, ����ġ ���� ���� ��ȯ���� Ȯ��
	COORD nextPos = nextHeadPos();
	if (detectCollision(nextPos.X, nextPos.Y) == 1)
		return;
	if (direction == 0 || direction == 1) return;

	// ���� ������Ʈ, �̵��� ���� head �� tail�� redraw
	direction = 0;
	drawHead(nextPos);
	eraseTail();
}

void shiftDown() // �÷��� �� down ����Ű �Է� ��
{
	COORD nextPos = nextHeadPos();
	if (detectCollision(nextPos.X, nextPos.Y) == 1)
		return;
	if (direction == 0 || direction == 1) return;

	direction = 1;
	drawHead(nextPos);
	eraseTail();
}

void shiftLeft() // �÷��� �� left ����Ű �Է� ��
{
	COORD nextPos = nextHeadPos();
	if (detectCollision(nextPos.X, nextPos.Y) == 1)
		return;
	if (direction == 2 || direction == 3) return;

	direction = 2;
	drawHead(nextPos);
	eraseTail();
}

void shiftRight() // �÷��� �� right ����Ű �Է� ��
{
	COORD nextPos = nextHeadPos();
	if (detectCollision(nextPos.X, nextPos.Y) == 1)
		return;
	if (direction == 2 || direction == 3) return;

	direction = 3;
	drawHead(nextPos);
	eraseTail();
}

int pausePlay() // �Ͻ����� -> ����� Ȥ�� ������ ��ٸ�
{
	int isDone = 0;

	while (1)
	{
		if (_kbhit() != 0)
		{
			int key = _getch();
			
			if (key == SPACE) break;
			else if (key == DOWN) isDone = 1;
			else if (key == UP) isDone = 0;
		}
		Sleep(10);
	}

	return isDone;
}

void goToStartScreen()
{
	// �ʿ��� �� �׸��� �Լ� ȣ��

	// ���� ���� �ʱ�ȭ
	direction = 0;
	stage = -1;
	speed = 20;
	shield = 0;
	for (int i = 0; i < 5; i++) fever[i] = 0;
	
	Moogi* p = head, * pi = p;
	while (p != NULL)
	{
		pi = p;
		p = p->right;
		free(pi);
	}
	COORD pos = { 20,20 };
	head = getNode(NULL, NULL, pos);
	pos.Y++;
	tail = getNode(head, NULL, pos);
	head->right = tail;
}

int detectCollision(int posX, int posY) // �浹 ����
{
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = (posY - GBOARD_ORIGIN_Y) / 2;

	switch (gameBoardInfo[arrX][arrY])
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	default:
		return 0;
	}
}

COORD nextHeadPos() // head�� ���� ��ġ ��ȯ
{
	COORD curPos;
	curPos.X = head->position.X;
	curPos.Y = head->position.Y;

	switch (direction)
	{
	case 0:
		curPos.Y--;
		break;
	case 1:
		curPos.Y++;
		break;
	case 2:
		curPos.X--;
		break;
	case 3:
		curPos.X++;
		break;
	default:
		break;
	}

	return curPos;
}

void drawHead(COORD headPos) // �̹����� �̵��� ���(head)
{
	Moogi* node = getNode(NULL, head, headPos);
	head = node;
	
	SetCurrentCursorPos(head->position.X, head->position.Y);
	printf("��");
	SetCurrentCursorPos(head->right->position.X, head->right->position.Y);
	printf("��");
}

void eraseTail() // �̹����� �̵��� ���(tail)
{
	SetCurrentCursorPos(tail->position.X, tail->position.Y);
	printf("  ");

	Moogi* tmp = tail;
	tail = tail->left;
	tail->right = NULL;
	free(tmp);
}

Moogi* getNode(Moogi* left, Moogi* right, COORD position)
{
	Moogi* node = (Moogi*)malloc(sizeof(Moogi));
	node->left = left;
	node->right = right;
	node->position = position;

	return node;
}