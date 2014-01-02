/*
 * StaticBox.cpp
 *
 *  Created on: 25 déc. 2013
 *      Author: louis
 */

#include <Entity/StaticBox.h>
#include "GameApp.h"
#include <GL/gl.h>
#include <GL/glu.h>

StaticBox::StaticBox(b2Vec2 pos, float32 largeur, float32 hauteur, float32 angle) : BoxEntity(pos,largeur, hauteur,angle) {

}

StaticBox::~StaticBox() {
}


b2BodyDef StaticBox::getBodyDef(){
	b2BodyDef body_def;
	body_def.type = b2_staticBody; //this will be a dynamic body
	body_def.position.Set(position_init.x,position_init.y); //a little to the left
	body_def.angle = angle_init;

	return body_def;
}
