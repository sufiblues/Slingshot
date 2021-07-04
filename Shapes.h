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
//line to line
glm::vec2 rayCast(glm::vec2 center, glm::vec2 ray, Line boundry);
//rect to line
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, Line boundry);
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, std::vector<Line> boundries);
//TODO: Rect to Rect casters
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, Rectangle block);
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, std::vector<Rectangle> blocks);
/*** Functions to change lines ***/
Line shift(Line line, glm::vec2 vector);
Line padLine(Line line, float pad);
glm::vec2 manhattanDistance(Line line);
glm::vec2 perpendicularVector(Line line);

//Depreciated
int collisionRectangleAndRectangle(Rectangle a, Rectangle b);

//used for mostly debug purposes.
std::vector<Line> boundinglines(Line boundry, Rectangle rect); 

/*** Render functions with no camera transformations ***/
void RenderShape(Line line, SDL_Color color);
void RenderShape(std::vector<Line> lines, SDL_Color);
void RenderShape(Circle circle,SDL_Color color);
void RenderShape(Rectangle rectangle, SDL_Color color);
/*** Render functions with camera transformations ***/
void RenderShape(Line line, SDL_Color color, int camera_x, int camera_y);
void RenderShape(std::vector<Line> lines, SDL_Color color, int camera_x, int camera_y);
void RenderShape(Circle circle, SDL_Color color, int camera_x, int camera_y);
void RenderShape(Rectangle rectangle, SDL_Color color, int camera_x, int camera_y);

/*** Debug Info ***/
void debugInfo(Line line, const char* name);
#endif // !_SHAPES_H
