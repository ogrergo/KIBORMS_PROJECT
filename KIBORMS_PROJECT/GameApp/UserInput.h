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
	typedef struct {
		bool key[SDLK_LAST];
		Timer* timers[SDLK_LAST];
	} KeyMap;

	KeyMap map;
};

#endif /* USERINPUT_H_ */
