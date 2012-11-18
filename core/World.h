#ifndef WORLD_H
#define	WORLD_H

#include "Particle.h"
#include "ForceGenerator.h"

class World
{
public:
	static const int MAX_PARTICLES = 1024;
	static const int MAX_FORCES = 1024;
	Particle *particles[MAX_PARTICLES];
	ForceGenerator *forces[MAX_FORCES];
	
	int numParticles;
	int numForces;
	
	World()
	{
		numParticles = 0;
		numForces = 0;
	}
	
	void AddParticle(Particle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
	}
	
	void AddForce(ForceGenerator *f)
	{
		if (numForces<MAX_FORCES)
			forces[numForces++] = f;
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
	}
};

#endif	/* WORLD_H */

