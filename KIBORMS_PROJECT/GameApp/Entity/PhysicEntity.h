/*
 * PhysicEntity.h
 *
 *  Created on: 26 déc. 2013
 *      Author: louis
 */

#ifndef PHYSICENTITY_H_
#define PHYSICENTITY_H_

#include <Entity/Entity.h>

class PhysicEntity: public Entity {
public:
	PhysicEntity();
	virtual ~PhysicEntity();

	virtual void initBody(b2Body* body);
	virtual b2BodyDef getBodyDef();

protected:
	b2Body* body;//la définition d'une entitée physique : elle peut etre dans box2D

};

#endif /* PHYSICENTITY_H_ */
