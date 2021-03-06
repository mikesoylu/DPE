#ifndef WORLD_H
#define	WORLD_H

// forward decleration for ContactGenerator
class World;
class ContactGenerator;

#include "Particle.h"
#include "Contact.h"
#include "ForceGenerator.h"
#include "ContactGenerator.h"

class World
{
public:
	static const int MAX_PARTICLES = 1024;
	static const int MAX_FORCES = 1024;
	static const int MAX_CONTACTS = 1024;
	static const int MAX_CONTACT_GENERATORS = 1024;
	
	Particle *particles[MAX_PARTICLES];
	ForceGenerator *forces[MAX_FORCES];
	Contact *contacts[MAX_CONTACTS];
	ContactGenerator *contactGenerators[MAX_CONTACTS];

	int numParticles;
	int numForces;
	int numContacts;
	int numContactGenerators;
	
	World()
	{
		numParticles = 0;
		numForces = 0;
		numContacts = 0;
		numContactGenerators = 0;
	}
	
	void AddParticle(Particle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
	}
	
	/** removes particle from everything then deletes it */
	void RemoveParticle(Particle *p)
	{
		// remove from contact generators
		for (int i = 0; i<numContactGenerators; i++)
		{
			if (contactGenerators[i]->RemoveParticle(p))
			{
				delete contactGenerators[i];
				if (1 == numContactGenerators)
					numContactGenerators = 0;
				else
				{
					contactGenerators[i--] = contactGenerators[--numContactGenerators];
				}
			}
		}
		// remove from force generators
		for (int i = 0; i<numForces; i++)
		{
			if (forces[i]->RemoveParticle(p))
			{
				delete forces[i];
				if (1 == numForces)
					numForces = 0;
				else
				{
					forces[i--] = forces[--numForces];
				}
			}
		}
		// lastly remove particle
		for (int i = 0; i<numParticles; i++)
		{
			if (particles[i] == p)
			{
				delete particles[i];
				if (1 == numParticles)
					numParticles = 0;
				else
				{
					particles[i--] = particles[--numParticles];
				}
			}
		}
	}
	void RemoveForceGenerator(ForceGenerator *f)
	{
			// lastly remove particle
		for (int i = 0; i<numForces; i++)
		{
			if (forces[i] == f)
			{
				if (1 == numForces)
					numForces = 0;
				else
				{
					forces[i--] = forces[--numForces];
				}
				delete f;
				return;
			}
		}
	}
	
	void AddForceGenerator(ForceGenerator *f)
	{
		if (numForces<MAX_FORCES)
			forces[numForces++] = f;
	}
	
	void AddContactGenerator(ContactGenerator *cg)
	{
		if (numContactGenerators<MAX_CONTACT_GENERATORS)
			contactGenerators[numContactGenerators++] = cg;
	}
	
	void AddContact(Contact *c)
	{
		if (numContacts<MAX_CONTACTS)
			contacts[numContacts++] = c;
	}
	
	void ClearContacts()
	{
		for (int i = 0; i < numContacts; i++)
		{
			delete contacts[i];
		}
		numContacts = 0;
	}
	
	void Advance(double dt)
	{
		// first apply forces
		for (int i = 0; i<numForces; i++)
		{
			forces[i]->ApplyForces();
		}
		
		// then integrate particles
		for (int i = 0; i<numParticles; i++)
		{
			particles[i]->Integrate(dt);
		}
		
		ClearContacts();
		
		// check contacts
		for (int i = 0; i<numContactGenerators; i++)
		{
			contactGenerators[i]->GenerateContacts();
		}
		
		// resolve contacts
		for (int i = 0; i<numContacts; i++)
		{
			contacts[i]->Resolve(dt);
		}
	}
};

#endif	/* WORLD_H */

