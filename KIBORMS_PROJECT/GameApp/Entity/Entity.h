/*
 * Entity.h
 *
 *  Created on: 25 déc. 2013
 *      Author: louis
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Box2D/Box2D.h"

class Entity {
public:
	Entity();
	virtual ~Entity();

	virtual void render();
	virtual void update();

protected:

	uint dpl_listID ;
	virtual void init_graphic();
};

#endif /* ENTITY_H_ */
