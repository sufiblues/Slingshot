#include "Level.h"

Level::~Level(){

}


void Level::addFloor(){
	for (int i = 0; i < columns; i++){
		addBlock(rows-1, i);
	}
}

Level::Level(int n, int r,int c){
	rows = r;
	columns = c;
	normalized = n;
 	level_center = glm::vec2(columns*normalized/2, rows*normalized/2);
	finished = false;	


	for (int i =0;i<rows;i++){
		std::vector<int> temp;
		temp.reserve(columns);
		for (int j = 0;j<columns;j++){
			temp.push_back(0);
		}
		board.push_back(temp);
	}	
}

void Level::setSpawnPoint(int r, int c){
	spawn_point = glm::vec2(r,c);
}

void Level::setEndPoint(int r, int c){
	end_point = glm::vec2(r, c);
	daEnd = {glm::vec2((end_point[1] * normalized) - normalized/2, ((rows - end_point[0])* normalized) - normalized/2) , normalized, normalized}; 
}

void Level::spawnCharacter(Player* mc){
		mc->hitbox.center = glm::vec2(spawn_point[1] * normalized, (rows - spawn_point[0]) * normalized);
}

void Level::reachedEndPoint(Player* mc){
	if (collisionRectangleAndRectangle(mc->hitbox, daEnd) > 0){
		finished = true;
	}
	else{
		finished = false;
	}
}

void Level::printBoard(){
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf(" %d ", board[i][j] );
		}
		printf("\n");
	}
}

void Level::showGridLines(int cx, int cy){
	SDL_SetRenderDrawColor(Renderer, 0xff,0xff,0xff,0xff);
	for (int i = 0; i<rows; i++){
		SDL_RenderDrawLine(Renderer, 0-cx, i * normalized -cy, columns*normalized -cx, i*normalized -cy);
	}
	for (int j=0; j<columns;j++){
		SDL_RenderDrawLine(Renderer , j*normalized -cx, 0 -cy, j*normalized -cx, rows*normalized -cy);
	}
}

bool Level::addBlock(int i, int j){
	if ((i >= rows) || (j >= columns) || i < 0 || j < 0){
		return false;
	}
	if (board[i][j] != 0){
		return false;
	}
	else{
		board[i][j] = 1;
		activeblocks.push_back(std::make_pair(i,j));
		Rectangle temp = {glm::vec2(j*normalized + normalized/2 , i*normalized + normalized/2 ), normalized, normalized};
		levelBlocks.push_back(temp);
		return true;
	}
}


bool Level::addHazardBlock(int i, int j){
	if ((i >= rows) || (j >= columns) || i < 0 || j < 0){
		return false;
	}
	if (board[i][j] != 0){
		return false;
	}
	else{
		board[i][j] = 2;
		activeblocks.push_back(std::make_pair(i,j));
		Rectangle temp = {glm::vec2(j*normalized + normalized/2 , i*normalized + normalized/2 ), normalized, normalized};
		hazardBlocks.push_back(temp);
		return true;
	}
}

void Level::playerCollideWithHazards(Player *mc){
	int res = 0;
	for (int i = 0; i < hazardBlocks.size(); i++){
		
		res = collisionRectangleAndRectangle(mc->hitbox,  hazardBlocks[i]) | res;
	}

	if (res){
		spawnCharacter(mc);
	}
}

void Level::loadAssets(){
	TextureID background = {SDL_Rect{0,0,normalized*columns,normalized*rows}, "bg"};	
	insertTexture("bg", "assets/textures/smash-3.jpg", &background.src);
	setTextureID(&background, "bg");
	renderable.push_back(background);
}

/*
void Level::renderAssets(int cx , int cy){
	for (int i = 0; i < renderable.size(); i++){
		RenderTextureID(&renderable[i], camera.x, camera.y);
	}
}
*/
void Level::drawBlock(int rp, int cp, int cx, int cy, SDL_Color color){
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect temp = {cp*normalized -camera.x , rp*normalized -camera.y, normalized, normalized};
	SDL_RenderFillRect(Renderer, &temp);	
}

void Level::renderBlocks(){
	for (int i = 0; i < activeblocks.size(); i++){
		if(board[activeblocks[i].first][activeblocks[i].second] == 1){
			drawBlock(activeblocks[i].first,activeblocks[i].second,camera.x,camera.y, green);
		} 
		else if(board[activeblocks[i].first][activeblocks[i].second] == 2){		
			drawBlock(activeblocks[i].first,activeblocks[i].second,camera.x,camera.y, red);
		}
	}
	//drawBlock((int) end_point[0],(int) end_point[1],camera.x,camera.y,red);
}

void Level::renderBackground(){
	RenderTextureID(&renderable[0], level_center );
}

int Level::playerCollideWithLevel(Circle* hitbox){
	int temp = 0;
	for (int i = 0; i < levelBlocks.size(); i++){
		temp = directionOfHit(hitbox, &levelBlocks[i]);
		if (temp != 0 ){
			return temp;
		} 
	}
	return temp;
}

void Level::Serialize(){
	std::ofstream testfile("pretty.json");
	nlohmann::json j;
	j["rows"] = rows;
	j["columns"] = columns;
	std::string levelFormat;
	for (int a = 0; a < board.size(); a++ ){
		for (int b = 0; b < board[a].size(); b++){
			levelFormat += "," + std::to_string(board[a][b]);
		}
		levelFormat += "\n";
	}
	j["board"] = levelFormat;
	testfile << j.dump();

}

void Level::Deserialize(std::string filename){
//get input file
	std::ifstream inputfile(filename);
	nlohmann::json jf = nlohmann::json::parse(inputfile);
//construct level from input file
	rows = jf["rows"];
	columns = jf["columns"];
	std::string levelFormat = jf["board"];
	std::cout << levelFormat;		
}
