/*
 * Interface.h
 *
 *  Created on: 2 janv. 2014
 *      Author: louis
 */

/**
 * Classe gérant les menus, la pause, les evenements claviers (couche menu)
 *
 */


#ifndef INTERFACE_H_
#define INTERFACE_H_


class Interface {
public:
	Interface();
	virtual ~Interface();

	void tick(float32 time_elapsed);
};

#endif /* INTERFACE_H_ */
