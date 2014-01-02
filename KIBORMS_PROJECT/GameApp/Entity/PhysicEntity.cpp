/*
 * PhysicEntity.cpp
 *
 *  Created on: 26 déc. 2013
 *      Author: louis
 */

#include <Entity/PhysicEntity.h>

PhysicEntity::PhysicEntity() {
	// TODO Auto-generated constructor stub

}

PhysicEntity::~PhysicEntity() {
	// TODO Auto-generated destructor stub
}

void PhysicEntity::initBody(b2Body* body){
	this->body = body;
}

b2BodyDef PhysicEntity::getBodyDef(){
	b2BodyDef body_def;
	return body_def;
}
