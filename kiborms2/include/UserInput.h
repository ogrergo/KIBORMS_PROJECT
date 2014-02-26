/*
 * UserInput.h
 *
 *  Created on: 22 déc. 2013
 *      Author: louis
 */

#ifndef USERINPUT_H_
#define USERINPUT_H_

#include <SDL/SDL.h>
#include "Timer/Timer.h"

class UserInput {
public:

	UserInput();
	virtual ~UserInput();

	void handle_SDLevent(SDL_Event* event);


private:
	int static const MAX_MOUSE = 4;

	typedef struct {
		bool key[SDLK_LAST];
		Timer* timers[SDLK_LAST];
		Uint16 x,y;
		bool mouse_key[3];
		Timer* mouse_timer[MAX_MOUSE];
	} KeyMap;

	KeyMap map;

};

#endif /* USERINPUT_H_ */
