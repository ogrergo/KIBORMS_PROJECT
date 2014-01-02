/*
 * StaticBox.h
 *
 *  Created on: 25 déc. 2013
 *      Author: louis
 */

#ifndef STATICBOX_H_
#define STATICBOX_H_

#include <Entity/BoxEntity.h>
#include <GL/gl.h>
#include <GL/glu.h>

class StaticBox: public BoxEntity {
public:
	StaticBox(b2Vec2 pos, float32 largeur, float32 hauteur, float32 angle = 0.0);
	virtual ~StaticBox();

	virtual b2BodyDef getBodyDef();
};

#endif /* STATICBOX_H_ */
