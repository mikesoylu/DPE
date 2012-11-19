#ifndef RODCONTACTGENERATOR_H
#define	RODCONTACTGENERATOR_H

#include "ContactGenerator.h"
#include "World.h"
#include "RodContact.h"


class RodContactGenerator: public ContactGenerator
{
public:
	Particle *particleA;
	Particle *particleB;
	
	double maxDist;
	
	RodContactGenerator(World *world)
	{
		this->world = world;
	}
	
	virtual void GenerateContacts()
	{
		world->AddContact(new RodContact(particleA, particleB, maxDist));
	}
};

#endif

