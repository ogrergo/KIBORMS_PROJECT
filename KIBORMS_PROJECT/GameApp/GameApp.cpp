/*
 * GameApp.cpp
 *
 *  Created on: 24 déc. 2013
 *      Author: louis
 */

#include <GameApp.h>


GameApp::GameApp() : App(){
	init();
	// TODO Auto-generated constructor stub

}

GameApp::~GameApp() {
	delete world;
}

void GameApp::init(){
	world = new World(FRAME_RATE);
}

void GameApp::render(){
	world->render();
}

void GameApp::update(){
	world->update();
}
