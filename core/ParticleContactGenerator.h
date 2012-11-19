#ifndef PARTICLECONTACTGENERATOR_H
#define	PARTICLECONTACTGENERATOR_H

#include "ContactGenerator.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "World.h"


class ParticleContactGenerator: public ContactGenerator
{
protected:
	static const int MAX_PARTICLES = 1024;

	Particle *particles[MAX_PARTICLES];
	int numParticles;
	
public:
	ParticleContactGenerator(World *world)
	{
		this->world = world;
		numParticles = 0;
	}
	
	void AddParticle(Particle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
	}
	
	// TODO: this should return true when it should be deleted
	/** WARNING: Does not delete the particle */
	virtual bool RemoveParticle(Particle *p)
	{
		// delete particle
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
		return false;
	}
	
	/** populates the contacts list in world */
	virtual void GenerateContacts()
	{
		for (int i = 0; i < numParticles-1; i++)
			for (int j = i+1; j < numParticles; j++)
			{
				Particle *pi = particles[i];
				Particle *pj = particles[j];
				Vector3 dd = pi->GetPosition() - pj->GetPosition();
				double min = pi->GetRadius() + pj->GetRadius();
				if (dd.Magnitude() <= min)
				{
					world->AddContact(new ParticleContact(pi, pj));
				}
			}
	}
};
#endif
