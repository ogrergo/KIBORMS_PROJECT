/*
 * BoxEntity.cpp
 *
 *  Created on: 26 déc. 2013
 *      Author: louis
 */

#include <Entity/BoxEntity.h>
#include "GameApp.h"

BoxEntity::BoxEntity(b2Vec2 pos, float32 largeur, float32 hauteur, float32 angle) {
	this->largeur = largeur;
	this->hauteur = hauteur;
	this->position_init = pos;
	this->angle_init = angle;

	init_graphic();
}

BoxEntity::~BoxEntity() {
	GameApp::freeDisplayList(dpl_listID);
}


b2BodyDef BoxEntity::getBodyDef(){
	b2BodyDef body_def;
	body_def.position.Set(position_init.x,position_init.y); //a little to the left
	body_def.angle = angle_init;

	return body_def;
}

void BoxEntity::initBody(b2Body* body){
	this->body = body;
	b2PolygonShape rectangle;
	rectangle.SetAsBox(largeur, hauteur, position_init , angle_init );
	b2FixtureDef fixture;
	fixture.shape = &rectangle;
	body->CreateFixture(&fixture);

}

void BoxEntity::render(){
	glPushMatrix();
	b2Vec2 pos = body->GetPosition();
	glTranslatef(pos.x, pos.y, 0.0);
	glRotatef(body->GetAngle(),0.0,0.0,1.0);
	printf("position : x%f y%f",pos.x,pos.y);
	GameApp::callDisplayList(dpl_listID);
	glPopMatrix();
}

void BoxEntity::init_graphic(){
	dpl_listID = GameApp::newDisplayList();
	glBegin(GL_TRIANGLES);

	glVertex2f(-largeur/2, -hauteur/2);
	glVertex2f(-largeur/2, +hauteur/2);
	glVertex2f(+largeur/2, +hauteur/2);

	glVertex2f(+largeur/2, +hauteur/2);
	glVertex2f(+largeur/2, -hauteur/2);
	glVertex2f(-largeur/2, -hauteur/2);

	glEnd();
	GameApp::endDisplayList();
}
