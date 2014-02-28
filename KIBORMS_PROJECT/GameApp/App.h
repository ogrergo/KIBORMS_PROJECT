/*
 * App.h
 *
 *  Created on: 2 nov. 2013
 *      Author: louis
 */

#ifndef APP_H_
#define APP_H_

#include <iostream>

#include <SDL/SDL.h>
#include "Timer/Timer.h"
#include "UserInput.h"
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

class App {
public:
	App();
	virtual ~App();

	/*
	 * Demarre l'App : charge le fichier de configu, lance les modules avec les bon paramètre et creer un objet interface, lance la boucle peridique en appellant la fonction tick() d'elle
	 */
	void run();

	/*
	 * Arrete l'App proprement
	 */
	void stop();

	/*
	 * Permet de creer une nouvelle display liste, et renvoie le handler.
	 * A bouger dans une classe static
	 */
	GLuint static newDisplayList();
	void static endDisplayList();
	void static freeDisplayList(uint displaylistID);
	void static callDisplayList(uint displaylistID);
protected:

	/*
	 * A true lorsque la boucle fonctionne
	 */
	bool running;

	/*
	 * Event à transferer
	 */
	SDL_Event event;

	int fps;
	double time_per_frame;

	//fonctionnemt du timer
	double accum_time;
	int accum_fps;
	Timer* timer;
	UserInput* key_manager;

	//variable utilisateur
	/*
	 * A charger par un fichier de conf
	 */
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int BIT_PER_PIXEL;
	bool FULLSCREEN;
	int FRAME_RATE;
	string TITLE;


	//fonctions à réécrire pour le programme
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void key_pressed();
	virtual void key_released();
	virtual void clean();

	void init_timer();
	void update_screen();
	void handle_event();
	void update_timer();


	void init_App(string conf);
	void load_conf(string conf);
	int init_SDL();
	int init_OPENGL();

	void clean_App();
	void clean_SDL();
private:
	uint static id_liste;
};

void err(string str);
void msg(string str);

#endif /* APP_H_ */
