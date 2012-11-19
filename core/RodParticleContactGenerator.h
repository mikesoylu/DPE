#ifndef RODPARTICLECONTACTGENERATOR_H
#define	RODPARTICLECONTACTGENERATOR_H

#include "ParticleContactGenerator.h"
#include "RodParticleContact.h"


class RodParticleContactGenerator:public ContactGenerator
{
protected:
	static const int MAX_RODS = 1024;
	static const int MAX_PARTICLES = 1024;

	Rod *rods[MAX_RODS];
	int numRods;
	
	Particle *particles[MAX_PARTICLES];
	int numParticles;
	
public:
	RodParticleContactGenerator(World *world)
	{
		this->world = world;
		numRods = 0;
		numParticles = 0;
	}
	
	void AddParticle(Particle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
	}
	
	// TODO: this should return true when it should be deleted
	/** also deletes Rods that have the particle */
	virtual bool RemoveParticle(Particle *p)
	{
		// remove particle
		for (int i = 0; i<numParticles; i++)
		{
			if (particles[i] == p)
			{
				if (1 == numParticles)
					numParticles = 0;
				else
					particles[i--] = particles[numParticles--];
			}
		}
		// delete rod
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
	
	void AddRod(Rod *r)
	{
		if (numRods<MAX_RODS)
			rods[numRods++] = r;
	}
	
	virtual void GenerateContacts()
	{
		for (int i = 0; i<numRods; i++)
			for (int j = 0; j<numParticles; j++)
			{
				Vector3 l = rods[i]->particleA->GetPosition() - rods[i]->particleB->GetPosition();
				l.Normalize();
				Vector3 d = particles[j]->GetPosition() - rods[i]->particleB->GetPosition();
				double dot = d*l;
				double cross = (d%l).Magnitude();
				if (dot > 0 && dot < rods[i]->maxDist && cross < particles[j]->GetRadius())
				{
					world->AddContact(new RodParticleContact(rods[i], particles[j]));
				}
			}
	}
	
	/** deletes rods because no one else uses them */
	~RodParticleContactGenerator()
	{
		// clear all rods
		for (int i = 0; i < numRods; i++)
			delete rods[i];
	}
};

#endif

