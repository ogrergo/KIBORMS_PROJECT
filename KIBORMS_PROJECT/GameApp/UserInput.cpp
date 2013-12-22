/*
 * UserInput.cpp
 *
 *  Created on: 22 déc. 2013
 *      Author: louis
 */

#include "UserInput.h"

#include <iostream>

UserInput::UserInput() {
	//on initialise la liste des touches.
	for(int i = 0; i < SDLK_LAST; i++){
		map.key[i] = false;
		map.timers[i] = new Timer();
	}
}

UserInput::~UserInput() {
	for(int i = 0; i < SDLK_LAST; i++){
		delete map.timers[i];
	}
}

void UserInput::handle_SDLevent(SDL_Event* event) {
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP){
		SDLKey code = event->key.keysym.sym;

		if (event->key.type == SDL_KEYDOWN){
			if ( ! map.key[code]){
				map.key[code] = true;
				map.timers[code]->start();
				//printf("key pressed : %d\n",code);
			}
		}else{
			map.key[code] = false;
			//printf("key released : %d ; time pressed : %f \n" ,code, map.timers[code]->getElapsedTime());
		}
	}else{
		if(event->type == SDL_MOUSEMOTION){
			printf("mouse mouve");
		}else{
			if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP){
				printf("mouse button");
			}
		}
	}
}
