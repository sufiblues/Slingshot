#include "Animation.h"

void renderAnimation(Animation * a, glm::vec2 pos){
	//do checks and updates at the start of the loop
	if (a->current_frame >= a->frames.size()-1){
		a->current_frame = 0;
		a->start_time = 0;
	}
	else if (a->start_time == a->frame_time[a->current_frame + 1]){
		a->current_frame += 1;
	}
//	printf("frame debug current frame %d  frame counter %d frames_size %d frames time size %d\n", a->current_frame, a->start_time, a->frames.size(), a->frame_time.size());	
	RenderTextureID(&a->frames[a->current_frame],pos);
	a->start_time += 1;
}

void addFrame(Animation* a, TextureID tid){
	a->frames.push_back(tid);
}

void addFrame(Animation* a, int time, std::string filepath){
	if (a->frames.size() == 0){
		time = 0;
		a->current_frame = 0;
	}
	else{
		if (a->frame_time.back() > time){
			printf("Error! Frame time mismatch!\n");
			return ;
		}
	}

	TextureID tid;
	//name should be something like running_0
	std::string tid_name = a->name + "_" + std::to_string(a->frames.size());	
	insertTexture(tid_name, filepath);
	setTextureID(&tid, tid_name);

	a->frames.push_back(tid);
	a->frame_time.push_back(time);
}
