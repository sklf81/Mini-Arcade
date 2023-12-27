#include <stdio.h>
#include "snakeGame.h"

Tail::Tail() {
	this->headPosition = new Vector2D;
	this->headPosition = &this->partsPosition[0];
	this->length = 1;
	this->resetPartsPositionArray();
	this->resetHeadPositionArray();
}

Tail::~Tail() {
	/*delete this->headPosition;
	delete[] Tail::partsPosition;
	delete[] Tail::latestHeadPositions;*/
}

void Tail::moveHead(Vector2D position) {
	this->headPosition->x = position.x;
	this->headPosition->y = position.y;
}

void Tail::pushParts() {
	for (byte i = 0; i < this->length; i++)
	{
		this->partsPosition[i].set(this->latestHeadPositions[i]);
	}
}

void Tail::addPart() {
	this->length++;
	this->partsPosition[this->length - 1].set(this->latestHeadPositions[this->length - 1]);
}

void Tail::updateHeadPositionArray() {
	for (byte i = this->length; i > 0; i--)
	{												
		this->latestHeadPositions[i] = this->latestHeadPositions[i - 1];
	}
	this->latestHeadPositions[0] = *this->headPosition;
}

void Tail::resetHeadPositionArray() {
	for (byte i = 0; i < FIELD_AREA; i++)
	{
		this->latestHeadPositions[i].set(-1, -1);
	}
	this->latestHeadPositions[0] = *this->headPosition;
}

void Tail::resetPartsPositionArray() {
	for (byte i = 0; i < FIELD_AREA; i++)
	{
		this->partsPosition[i].set(-1, -1);
	}
	this->headPosition->set(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);
}

Snake::Snake() {
	this->tail.partsPosition[0].set(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);
	this->headPosition = new Vector2D();
	this->headPosition = &this->tail.partsPosition[0];
	this->tail.length = 1;
}
Snake::~Snake() {
	delete this->headPosition;
	delete this->foodposition;
}
bool Snake::eatsFood() {
	if (this->foodposition->equals(*this->headPosition)) {
		return true;
	}
	else
		return false;
}
bool Snake::hitsBorder() {
	if (this->headPosition->x > FIELD_WIDTH || this->headPosition->y > FIELD_HEIGHT ||
		this->headPosition->x < 0 || this->headPosition->y < 0) {
		return true;
	}
	else
		return false;
}
bool Snake::hitsItself() {
	for (byte i = 1; i < this->tail.length; i++)
	{
		if (this->tail.headPosition->equals(this->tail.partsPosition[i]))
			return true;
	}
	return false;
}
void Snake::move(s_byte x, s_byte y) {
	this->tail.moveHead(Vector2D(this->headPosition->x + x, this->headPosition->y + y));
	this->tail.updateHeadPositionArray();
	this->tail.pushParts();
}

void Snake::reset() {
	this->tail.resetHeadPositionArray();
	this->tail.resetPartsPositionArray();
	this->headPosition->set(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);
	this->tail.length = 1;
}