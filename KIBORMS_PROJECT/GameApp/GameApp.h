/*
 * GameApp.h
 *
 *  Created on: 24 déc. 2013
 *      Author: louis
 */

#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "App.h"
#include "World.h"

class GameApp : public App{
public:
	GameApp();
	virtual ~GameApp();

protected:
	World* world;

	void init();
	void render();
	void update();
};

#endif /* GAMEAPP_H_ */
