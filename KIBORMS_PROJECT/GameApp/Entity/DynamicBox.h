/*
 * DynamicBox.h
 *
 *  Created on: 26 déc. 2013
 *      Author: louis
 */

#ifndef DYNAMICBOX_H_
#define DYNAMICBOX_H_

#include <Entity/BoxEntity.h>

class DynamicBox: public BoxEntity {
public:
	DynamicBox(b2Vec2 pos, float32 largeur, float32 hauteur, float32 angle);
	virtual ~DynamicBox();

	virtual b2BodyDef getBodyDef();

};

#endif /* DYNAMICBOX_H_ */
