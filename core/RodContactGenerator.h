#ifndef RODCONTACTGENERATOR_H
#define	RODCONTACTGENERATOR_H

#include "ContactGenerator.h"
#include "World.h"
#include "RodContact.h"
#include "Rod.h"

class RodContactGenerator: public ContactGenerator
{
protected:
	static const int MAX_RODS = 1024;

	Rod *rods[MAX_RODS];
	int numRods;
	
public:
	RodContactGenerator(World *world)
	{
		this->world = world;
	}
	
	void AddRod(Rod *r)
	{
		if (numRods<MAX_RODS)
			rods[numRods++] = r;
	}
	
	virtual void GenerateContacts()
	{
		for (int i = 0; i < numRods-1; i++)
			world->AddContact(new RodContact(rods[i]));
	}
};

#endif

