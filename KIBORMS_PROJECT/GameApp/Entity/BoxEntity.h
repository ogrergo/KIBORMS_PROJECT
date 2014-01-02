/*
 * BoxEntity.h
 *
 *  Created on: 26 déc. 2013
 *      Author: louis
 */

#ifndef BOXENTITY_H_
#define BOXENTITY_H_

#include <Entity/PhysicEntity.h>

class BoxEntity: public PhysicEntity {
public:
	BoxEntity(b2Vec2 pos, float32 largeur, float32 hauteur, float32 angle = 0.0);
	virtual ~BoxEntity();

	virtual void initBody(b2Body* body);
	virtual b2BodyDef getBodyDef();

	virtual void render();

protected:
	b2Vec2 position_init;
	float32 angle_init;
	float32 hauteur, largeur;

	virtual void init_graphic();
private:
	uint dpl_listID;
};

#endif /* BOXENTITY_H_ */
