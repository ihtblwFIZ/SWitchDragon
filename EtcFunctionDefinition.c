#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#include "EtcFunction.h"

int countScore(int currentScore) {
	if (detectCollision(head->position.X, head->position.Y) == 3) {
		currentScore += 5;
	}

	return currentScore;
}

void getBestScore() {	//���� ���� �� �÷��� ���� �ݵ�� �ҷ��� �Ѵ�...(1����)
	FILE* fp_r = fopen("BestScore.txt", "r");
	if (fp_r == NULL) {
		//printf("����\n");
		return;
	}
	//printf("����!!\n");
	for (int i = 0; i < 5; i++) {
		fscanf(fp_r, "%d", &stageBestScore[i]);
	}
	fclose(fp_r);		//���Ͽ��� �ְ����� ���� �� ���� ���� stageBestScore�迭�� ����
}

void setBestScore(int currentScore) {			//���ӿ����������� �θ��� �� ��?
	if (currentScore > stageBestScore[stage - 1]) {
		stageBestScore[stage - 1] = currentScore;
	}
}

void saveBestScore() {	//���� ���� �� �ٽ� �ְ������� ���Ͽ� �����ϴ� ����
	FILE* fp_w = fopen("BestScore.txt", "w");
	for (int i = 0; i < 5; i++) {
		fprintf(fp_w, "%d\n", stageBestScore[i]);
	}
	fclose(fp_w);
}

int isGameOver() {		//���ϰ��� 1�̸� ���������ؾߵ�
	if (detectCollision(head->position.X, head->position.Y) == 1) {
		return 1;		//������ 1����
	}
	return 0;			//�ƴϸ� 0
}

void getItem() {
	/*���ο��� �̰� �ҷ��ߵ�
	srand((unsigned int)time(NULL));*/
	int goodOrBad = detectCollision(head->position.X, head->position.Y);
	if (goodOrBad == 4) {	//����������(���̡�, �ӵ���, FEVER, �ǵ�, �����ֻ���)
		int item = (rand() % 2) + 1;//(rand() % 5) + 1; ���� �̰ǵ� ������ ������ 2����
		switch (item) {
		case 1:		//���̡�
			deleteBody(tail);
			//setCurrentCursorPos(��������ġ..);
			printf("���� ����!");
			break;
		case 2:		//�ӵ���
			speedDown(speed);
			//setCurrentCursorPos(��������ġ..);
			printf("�ӵ� ����!");
			break;
		}
	}
	else if (goodOrBad == 5) {	//������������ (���̡�, �ӵ���)
		int item = (rand() % 2) + 1;
		switch (item) {
		case 1:		//���̡�
			addBody(tail);
			break;
		case 2:		//�ӵ���
			speedUp(speed);
			break;
		}
	}

	//0 �ƹ��͵����°�, 1 ����ֹ�, 2 �̹����, 3 ������, 4 ����������, 5 ���۾�����,
}

void addDragonBall() {
	while (1) {
		int arrX = (rand() % (GBOARD_WIDTH - GBOARD_ORIGIN_X)) / 2;
		int arrY = rand() % (GBOARD_HEIGHT - GBOARD_ORIGIN_Y);
		if (gameBoardInfo[arrX][arrY] == 0) {
			gameBoardInfo[arrX][arrY] = 3;
			showDragonBall(arrX, arrY);
			return;
		}
	}
}

void showDragonBall(int arrX, int arrY) {
	setCurrentCursorPos(arrX, arrY);
	printf("��");
}