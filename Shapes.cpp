#include "Shapes.h"


/** [0:NONE] [1:TOP] [2:BOTTOM] [3:LEFT] [4:RIGHT] */
//TODO: Fix the pointer shit to this function
int collisionRectangleAndRectangle(Rectangle a, Rectangle b){
    int w = (a.width + b.width)/2;
    int h = (a.height + b.height)/2;
    int dx = a.center[0] - b.center[0];
    int dy = a.center[1] - b.center[1];

    if (abs(dx) <= w && abs(dy) <= h){
       int wy = w * dy;
       int hx = h * dx;
        
       if (wy > hx){
           if (wy > -hx){
               //return top
               printf("TOP\n");
	       //a->center[1] = a->center[1] +  ((dy * (h - abs(dy)))/abs(dy));
               return (1 << 1);
           }
           else{
               //return RIGHT
               printf("RIGHT\n");
               //a->center[0] = a->center[0] +  ((dx * (h - abs(dx)))/abs(dx));
               return (1 << 3);
           }
       }
       else{
           if (wy <= -hx){
               //return bot
               printf("BOTTOM\n");
	       //a->center[1] = a->center[1] +  ((dy * (h - abs(dy)))/abs(dy));
               return (1 << 1);
           }
           else{
               //return left  
	       printf("LEFT\n");
               //a->center[0] = a->center[0] +  ((dx * (h - abs(dx)))/abs(dx));
               return (1 << 2);
           }
       }
    }
    else{
        return 0;
    }  
}

void RenderShape(Circle circle, SDL_Color color) {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);

    int sides = 20;
    if (sides == 0)
    {
        sides = M_PI * circle.radius;
    }

    float d_a = 2 * M_PI / sides,
        angle = d_a;

    glm::vec2 start, end;
    end.x = circle.radius;
    end.y = 0.0f;
    end = end + circle.center;
    for (int i = 0; i != sides; i++)
    {
        start = end;
        end.x = cos(angle) * circle.radius;
        end.y = sin(angle) * circle.radius;
        end = end + circle.center;
        angle += d_a;
        SDL_RenderDrawLine(Renderer, start[0], start[1], end[0], end[1]);
    }
}

void RenderShape(Circle circle, SDL_Color color, int camera_x, int camera_y) {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);

    glm::vec2 cam_center = circle.center;
    cam_center[0] = cam_center[0] - camera_x;
    cam_center[1] = cam_center[1] - camera_y;

    int sides = 10;
    if (sides == 0)
    {
        sides = M_PI * circle.radius;
    }

    float d_a = 2 * M_PI / sides,
        angle = d_a;

    glm::vec2 start, end;
    end.x = circle.radius;
    end.y = 0.0f;
    end = end + cam_center;
    for (int i = 0; i != sides; i++)
    {
        start = end;
        end.x = cos(angle) * circle.radius;
        end.y = sin(angle) * circle.radius;
        end = end + cam_center;
        angle += d_a;
        SDL_RenderDrawLine(Renderer, start[0], start[1], end[0], end[1]);
    }
}


glm::vec2 Cast(glm::vec2 center, glm::vec2 ray, Line boundry){
	int x1 = center[0];
	int x2 = center[0] + ray[0];
	int y1 = center[1];
	int y2 = center[1] + ray[1];

	int x3 = boundry.one[0];
	int x4 = boundry.two[0];
	int y3 = boundry.one[1];
	int y4 = boundry.two[1];

	float den = (x1 - x2) * ( y3-y4) - (y1-y2) * (x3 - x4);
	//den == 0 means that the lines are parallel and divide by zero will cause crashes
	if (den == 0){
	    return glm::vec2(-1,-1);
	}
	
	
	
	float t = ((x1 - x3)*(y3-y4) - (y1 - y3) * (x3 - x4))/ den;
        float u = -((x1 - x2)*(y1-y3) - (y1 - y2) * (x1 - x3))/ den;
	
	

	return glm::vec2(t,u);
}

//shift a line by a 2d vector.
Line shift(Line line, glm::vec2 vector){
	Line res = line;
	res.one = line.one + vector;
	res.two = line.two +  vector;
	return res;
}

//calculates the manhattan distance of a line
glm::vec2 manhattanDistance(Line line){
	return glm::vec2(line.two[0] - line.one[0], line.two[1] - line.one[1]);
}

glm::vec2 perpendicularVector(Line line){	
	return glm::vec2(line.two[1] - line.one[1], -(line.two[0] - line.one[0]));
}
//pads line with a scalar amount from center out.
Line padLine(Line line, float pad){
    glm::vec2 point_one_pad = glm::normalize(manhattanDistance(line))* (-1*(pad/2));
    glm::vec2 point_two_pad = glm::normalize(manhattanDistance(line))*(pad/2);
   
    //round off normalized vector in order to make sure that the calculated lines are integers. 
    line.one = line.one + (point_one_pad);
    line.two = line.two + (point_two_pad);
	
    return line;
}

void debugInfo(Line line,const char* name ){
    printf("Name: %s Point one (%f,%f) Point two: (%f,%f)\n", name, line.one[0], line.one[1], line.two[0], line.two[1]);
}

//TODO: Create a roundline function. Ideally the rounding would occur after all transformations are done on the object.

//constructs bounding lines from a line and rectangle
std::vector<Line> boundinglines(Line boundry, Rectangle rect){
	//putting ceil because i Would much rather a character be one pixel above a boundry than inside it.
	float padding = ceil(sqrt(pow((float)rect.width,2) + pow((float)rect.height,2)));		

	Line m1 = padLine(shift(boundry, round(glm::normalize(perpendicularVector(boundry)))*round(glm::vec2(rect.width/2, rect.height/2))), padding);

	Line m2 = padLine(shift(boundry, round(glm::normalize(perpendicularVector(boundry)))*round(glm::vec2(-rect.width/2, -rect.height/2))),padding);

	Line m3 = {m1.one, m2.one};

	Line m4 = {m1.two, m2.two};

	std::vector<Line> outline;
	outline.reserve(4);
	//construct 4 boundries to account for the width of the rectangle
	outline.push_back(m1);
	outline.push_back(m2);	
	outline.push_back(m3);
	outline.push_back(m4);

	return outline;
	

}

//TODO: Can be speed up by not creating new padding per line
glm::vec2 Cast(Rectangle rect, glm::vec2 ray, std::vector<Line> boundries){
	glm::vec2 tandu = glm::vec2(1,1);

	for (int i =0 ; i < boundries.size(); i++){
	    glm::vec2 temp = Cast(rect, ray, boundries[i]);
	    if (temp[0] < 1 && temp[0] >= 0){
	    	if (temp[0] < tandu[0]){
		    tandu = temp;
		}
	    }
	}

	return tandu;
}

glm::vec2 Cast(Rectangle rect, glm::vec2 ray, Line boundry){

	
	//create a pad 	
	float padding = ceil(sqrt(pow((float)rect.width,2) + pow((float)rect.height,2)));		

	Line m1 = padLine(shift(boundry, round(glm::normalize(perpendicularVector(boundry)))*round(glm::vec2(rect.width/2, rect.height/2))), padding);

	Line m2 = padLine(shift(boundry, round(glm::normalize(perpendicularVector(boundry)))*round(glm::vec2(-rect.width/2, -rect.height/2))),padding);	

	Line m3 = {m1.one, m2.one};

	Line m4 = {m1.two, m2.two};

	std::vector<Line> outline;
	outline.reserve(4);
	//construct 4 boundries to account for the width of the rectangle
	outline.push_back(m1);
	outline.push_back(m2);	
	outline.push_back(m3);
	outline.push_back(m4);
	
	glm::vec2 tandu = glm::vec2(1,1);
	//iterate through the lines in order to find the smallest t and u
	for (int i = 0; i < outline.size(); i++){
	    glm::vec2 temp = Cast(rect.center, ray, outline[i]);
	    if (temp[0] < 1 && temp[0] >= 0){ 
	       if (temp[0] < tandu[0]){
	           tandu = temp;
	       }
	    }
	}
	
	return tandu;
}

void RenderShape(std::vector<Line> lines, SDL_Color color){
	
	for (int i = 0; i < lines.size(); i++){
		RenderShape(lines[i],color);
	}
}

void RenderShape(Line line, SDL_Color color){
    SDL_SetRenderDrawColor(Renderer, color.r,color.g,color.b, color.a);

    SDL_RenderDrawLine(Renderer, line.one[0],line.one[1],line.two[0],line.two[1]);
}


void RenderShape(Rectangle rectangle, SDL_Color color, int camera_x, int camera_y){
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b,color.a);

    glm::vec2 cam_center = rectangle.center;
    cam_center[0] = cam_center[0] - camera_x;
    cam_center[1] = cam_center[1] - camera_y;
    
    SDL_Rect temp = {(int)(rectangle.center[0] - rectangle.width / 2) - camera_x, (int)(rectangle.center[1] - rectangle.height / 2) - camera_y, rectangle.width, rectangle.height };
    SDL_RenderFillRect(Renderer, &temp);
}

void RenderShape(Rectangle rectangle, SDL_Color color) {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
    SDL_Rect temp = { (int) (rectangle.center[0] - rectangle.width / 2) , (int)(rectangle.center[1] - rectangle.height / 2), rectangle.width, rectangle.height };
    SDL_RenderFillRect(Renderer, &temp);
}


