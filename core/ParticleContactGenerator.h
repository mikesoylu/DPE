#ifndef PARTICLECONTACTGENERATOR_H
#define	PARTICLECONTACTGENERATOR_H

#include "ContactGenerator.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "World.h"


class ParticleContactGenerator: public ContactGenerator
{
	static const int MAX_PARTICLES = 1024;

	Particle *particles[MAX_PARTICLES];
	int numParticles;
	
public:
	ParticleContactGenerator(World *world)
	{
		numParticles = 0;
		this->world = world;
	}
	
	void AddParticle(Particle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
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
