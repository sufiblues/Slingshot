#pragma once
#ifndef _SHAPES_H
#define _SHAPES_H

#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "Context.h"
#include <stdio.h>


typedef struct Point {
	glm::vec2 Pos;
} Point;

typedef struct Circle {
	glm::vec2 center;
	int radius;
} Circle;

typedef struct Rectangle {
	glm::vec2 center;
	int width;
	int height;
} Rectangle;

int getLeftX(Rectangle* rect);
int getRightX(Rectangle* rect);
int getTopY(Rectangle* rect);
int getBottomY(Rectangle* rect);

bool collisionCircleAndRectangle(Circle *circle, Rectangle *rect);
bool collisionRectangleAndRectangle(Rectangle *a, Rectangle *b);
bool collisionPointInShape(Point *p, Circle *circle);
bool collisionPointInShape(Point *p, Rectangle *rectangle);
/*** [0:NONE] [1:LEFT] [2:RIGHT] [3:TOP] [4:DOWN] [5:CORNER] ***/
int directionOfHit(Circle *circle, Rectangle *rect);

void debugInfo(Rectangle rectangle,bool coordinates = false);
void debugInfo(Circle circle);
void debugInfo(Point point);

void RenderShape(Circle* circle,SDL_Color color);
void RenderShape(Rectangle* rectangle, SDL_Color color);
void RenderShape(Circle* circle, SDL_Color color, int camera_x, int camera_y);
void RenderShape(Rectangle* rectangle, SDL_Color color, int camera_x, int camera_y);

#endif // !_SHAPES_H
