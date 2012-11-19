#ifndef CONTACTGENERATOR_H
#define	CONTACTGENERATOR_H

#include "World.h"
#include "Contact.h"

class ContactGenerator
{
protected:
	World *world;
public:
	void (*contactCallback)(Contact *contact);
	virtual void GenerateContacts() = 0;
};

#endif