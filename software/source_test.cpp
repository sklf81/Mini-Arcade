/*
	---------------------------------------------------------
	This is an example for the use of the "SnakeGame" library
	
	If you compile this, you should be able to play Snake in
	your console.
	---------------------------------------------------------
*/


#define _CRT_SECURE_NO_WARNINGS

#include "snakeGame.h"
#include <stdio.h>
#include <Windows.h>
#include <ctime>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8


void renderPoint(Vector2D point[]);
void setMoveDirection(Vector2D* moveDirection);

int main() {
	SnakeGame snakeg;
	char input;

	Vector2D moveDirection;
	moveDirection.x = 1;
	moveDirection.y = 0;

	std::clock_t start;
	start = clock();

	snakeg.reset();

	do  {
		setMoveDirection(&moveDirection);
		if (std::clock() - start >= 200) {
			start = clock();
			system("cls");

			if (snakeg.snake.eatsFood()) {
				snakeg.snake.tail.addPart();
				snakeg.spawnFood();
			}
			if (snakeg.snake.hitsBorder() || snakeg.snake.hitsItself()) {
				snakeg.reset();
			}

			snakeg.setObjectPositions();
			snakeg.snake.move(moveDirection.x, moveDirection.y);
			renderPoint(snakeg.objectPositions);
		}	
	} while (!GetAsyncKeyState(VK_RETURN));

	system("pause");

	return 0;
}

void renderPoint(Vector2D point[]) {
	bool pointSet = false;
	for (size_t i = 0; i < FIELD_WIDTH; i++)
	{
		printf("-");
	}
	printf("\n");
	for (size_t i = 0; i <= FIELD_HEIGHT; i++)
	{
		for (size_t j = 0; j <= FIELD_WIDTH; j++)
		{
			pointSet = false;
			for (size_t k = 0; !point[k].equals(Vector2D('N','D')); k++)
			{
				if (point[k].x == j && point[k].y == i) {
					pointSet = true;
					printf("#");
				}
			}
			if (!pointSet) {
				printf(".");
			}
		}
		printf("|");
		printf("\n");
	}
	for (size_t i = 0; i < FIELD_WIDTH; i++)
	{
		printf("-");
	}
	printf("\n");
}

void setMoveDirection(Vector2D* moveDirection) {
	if (GetAsyncKeyState(VK_LEFT)) {
		moveDirection->x = -1;
		moveDirection->y = 0;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		moveDirection->x = 1;
		moveDirection->y = 0;
	}

	if (GetAsyncKeyState(VK_UP)) {
		moveDirection->y = -1;
		moveDirection->x = 0;
	}

	if (GetAsyncKeyState(VK_DOWN)) {
		moveDirection->y = 1;
		moveDirection->x = 0;
	}
}
