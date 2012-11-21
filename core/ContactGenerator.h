#ifndef CONTACTGENERATOR_H
#define	CONTACTGENERATOR_H

#include "Contact.h"


class World;
class Contact;
class Particle;

class ContactGenerator
{
protected:
	World *world;
public:
	void (*contactCallback)(Contact *contact);
	
	ContactGenerator()
	{
		contactCallback = 0;
	}
	
	virtual void GenerateContacts() = 0;
	// this should return true when it self should be deleted (eg. does nothing)
	virtual bool RemoveParticle(Particle *p) = 0;
};

#endif