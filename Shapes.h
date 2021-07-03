#pragma once
#ifndef _SHAPES_H
#define _SHAPES_H

#include "Utils.h"
#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "Context.h"
#include <stdio.h>
#include <vector>

typedef struct Point {
	glm::vec2 Pos;
} Point;

typedef struct Line {
	glm::vec2 one;
	glm::vec2 two;
} Line;

typedef struct Circle {
	glm::vec2 center;
	int radius;
} Circle;

typedef struct Rectangle {
	glm::vec2 center;
	int width;
	int height;
} Rectangle;
/*** return t,u which are used to figure out intersection on the two line segments ***/
glm::vec2 Cast(glm::vec2 center, glm::vec2 ray, Line boundry);
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, Line boundry);
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, std::vector<Line> boundries);
Line shift(Line line, glm::vec2 vector);

glm::vec2 manhattanDistance(Line line);
glm::vec2 perpendicularVector(Line line);

bool collisionCircleAndRectangle(Circle circle, Rectangle rect);
int collisionRectangleAndRectangle(Rectangle a, Rectangle b);

std::vector<Line> boundinglines(Line boundry, Rectangle rect); 

void RenderShape(std::vector<Line> lines, SDL_Color);
void RenderShape(Line line, SDL_Color color);
void RenderShape(Circle circle,SDL_Color color);
void RenderShape(Rectangle rectangle, SDL_Color color);
void RenderShape(Circle circle, SDL_Color color, int camera_x, int camera_y);
void RenderShape(Rectangle rectangle, SDL_Color color, int camera_x, int camera_y);

void debugInfo(Line line, const char* name);
#endif // !_SHAPES_H
