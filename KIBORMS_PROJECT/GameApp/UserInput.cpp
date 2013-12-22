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
	for(int i = 0; i < MAX_MOUSE; i++){
		map.mouse_key[i] = false;
		map.mouse_timer[i] = new Timer();
	}
}

UserInput::~UserInput() {
	for(int i = 0; i < SDLK_LAST; i++){
		delete map.timers[i];
	}
	for(int i = 0; i < MAX_MOUSE; i++){
		delete map.mouse_timer[i];
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
			map.x = event->motion.x;
			map.y = event->motion.y;
			//printf("mouse move: %d,%d\n",map.x,map.y);
		}else{
			if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP){
				if(event->button.state == SDL_PRESSED && event->button.button < MAX_MOUSE ){
					map.mouse_key[event->button.button] = true;
					map.mouse_timer[event->button.button]->start();
					//printf("souris appuyé\n");
				}else{
					if( event->button.button < MAX_MOUSE){
						map.mouse_key[event->button.button] = false;
						//printf("souris relevé  time : %f\n",map.mouse_timer[event->button.button]->getElapsedTime());
					}else{
						printf("erreur touche souris non assigné !\n");
					}
				}
			}
		}
	}
}
