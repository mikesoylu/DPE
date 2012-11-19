#ifndef ROD_H
#define	ROD_H

#include "Particle.h"

class Rod
{
public:
	Particle *particleA;
	Particle *particleB;
	
	double maxDist;
	
	Rod(Particle *particleA, Particle *particleB, double maxDist = -1.0)
	{
		this->particleA = particleA;
		this->particleB = particleB;
		
		if (maxDist<0)
		{
			maxDist = (particleA->GetPosition()-particleB->GetPosition()).Magnitude();
		}
		this->maxDist = maxDist;
	}
};

#endif

