#ifndef CONTACTGENERATOR_H
#define	CONTACTGENERATOR_H

#include "World.h"

class ContactGenerator
{
protected:
	World *world;
public:
	virtual void GenerateContacts() = 0;
};

#endif