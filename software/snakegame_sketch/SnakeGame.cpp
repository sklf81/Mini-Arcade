#include "snakeGame.h"
#include <time.h>

Vector2D::Vector2D() {
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(s_byte x, s_byte y) {
	this->x = x;
	this->y = y;
}

void Vector2D::set(Vector2D position) {
	this->x = position.x;
	this->y = position.y;
}

void Vector2D::set(s_byte x, s_byte y) {
	this->x = x;
	this->y = y;
}

bool Vector2D::equals(Vector2D compPartner) {
	return (compPartner.x == this->x && compPartner.y == this->y) ? true : false;
}


SnakeGame::SnakeGame() {
	srand(time(NULL));
	this->foodposition.x = rand() % (FIELD_WIDTH);
	this->foodposition.y = rand() % (FIELD_HEIGHT);
	this->snake.foodposition = &this->foodposition;
}

SnakeGame::~SnakeGame() {
	delete[] SnakeGame::objectPositions;
}

void SnakeGame::reset() {
	srand(time(NULL));
	snake.reset();
	this->spawnFood();
	this->setObjectPositions();
}

void SnakeGame::spawnFood() {
	this->foodposition.x = rand() % (FIELD_WIDTH + 1);
	this->foodposition.y = rand() % (FIELD_HEIGHT + 1);
	for (byte i = 0; i < this->snake.tail.length; i++)
	{
		if (foodposition.equals(snake.tail.partsPosition[i])) {
			this->foodposition.x = rand() % (FIELD_WIDTH + 1);
			this->foodposition.y = rand() % (FIELD_HEIGHT + 1);
			i = 0;
		}
	}
}

void SnakeGame::setObjectPositions() {
	byte i;
	for (i = 0; !this->snake.tail.partsPosition[i].equals(Vector2D(-1, -1)); i++)
	{
		this->objectPositions[i] = this->snake.tail.partsPosition[i];
	}
	this->objectPositions[i + 1].set('N', 'D');
	this->objectPositions[i] = this->foodposition;
}