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
		numRods = 0;
	}
	
	void AddRod(Rod *r)
	{
		if (numRods<MAX_RODS)
			rods[numRods++] = r;
	}
	
	virtual void GenerateContacts()
	{
		for (int i = 0; i < numRods; i++)
			world->AddContact(new RodContact(rods[i]));
	}
	
	// TODO: this should return true when it should be deleted
	/** deletes Rods that have the particle */
	virtual bool RemoveParticle(Particle *p)
	{
		for (int i = 0; i < numRods; i++)
		{
			if (rods[i]->particleA == p || rods[i]->particleB == p)
			{
				delete rods[i];
				if (1 == numRods)
					numRods = 0;
				else
					rods[i--] = rods[numRods--];
			}
		}
		return false;
	}
	
	/** deletes rods because no one else uses them */
	~RodContactGenerator()
	{
		// clear all rods
		for (int i = 0; i < numRods; i++)
			delete rods[i];
	}
};

#endif

