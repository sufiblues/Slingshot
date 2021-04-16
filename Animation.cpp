#include "Animation.h"

void renderAnimation(Animation * a, glm::vec2 pos, int frame){
	if (frame >= a->frames.size()){
		printf("Animation Error! Frame reference exceeds number of frames in animation\n");
	}
	else{
		RenderTextureID(&a->frames[frame],pos);
	}

}

void addFrame(Animation* a, TextureID tid){
	a->frames.push_back(tid);
}

void addFrame(Animation* a, std::string filepath){
	TextureID tid;
	//name should be something like running_0
	std::string tid_name = a->name + "_" + std::to_string(a->frames.size());	
	insertTexture(tid_name, filepath);
	setTextureID(&tid, tid_name);

	a->frames.push_back(tid);
}
