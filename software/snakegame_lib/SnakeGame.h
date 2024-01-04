#ifndef SNAKEG_H
#define SNAKEG_H

#include <stdlib.h>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8
#define FIELD_AREA FIELD_WIDTH * FIELD_HEIGHT

typedef unsigned char byte;
typedef char s_byte;


class Vector2D {
public:
	s_byte x;
	s_byte y;
	Vector2D();
	Vector2D(s_byte x, s_byte y);
	void set(Vector2D position);
	void set(s_byte x, s_byte y);
	bool equals(Vector2D compPartner);
};

class Tail {
public:
	Vector2D partsPosition[FIELD_AREA];
	byte length;
	Vector2D* headPosition;
	Vector2D latestHeadPositions[FIELD_AREA];
	Tail();
	~Tail();
	void moveHead(Vector2D position);
	void pushParts();
	void addPart();
	void updateHeadPositionArray();
	void resetHeadPositionArray();
	void resetPartsPositionArray();
};

class Snake : public Tail{
public:
	Tail tail;
	Vector2D* foodposition;
	Vector2D* headPosition;
	Snake();
	~Snake();
	bool eatsFood();
	bool hitsBorder();
	bool hitsItself();
	void move(s_byte x, s_byte y);
	void reset();
};

class SnakeGame{
public:
	Vector2D foodposition;
	Snake snake;
	Vector2D objectPositions[FIELD_AREA];
	SnakeGame();
	~SnakeGame();
	void reset();
	void spawnFood();
	void setObjectPositions();
};
#endif
