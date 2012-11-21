#ifndef EMITTER_H
#define EMITTER_H

#include <cmath>
#include <vector>
#include "EmittedParticle.h"
#include "Vector3.h"
#include "Util.h"

using std::vector;

class Emitter
{
protected:
	static const int MAX_PARTICLES = 512;
	
public:
	EmittedParticle *particles[MAX_PARTICLES];
	int numParticles;
	
	double life;
	double lifeVar;

	Vector3 position;
	Vector3 velocity;
	Vector3 velocityVar;

	Emitter(Vector3 position, Vector3 velocity, double life, Vector3 velocityVar, double lifeVar)
	{
		this->position = position;
		this->velocity = velocity;
		this->velocityVar = velocityVar;

		this->life = life;
		this->lifeVar = lifeVar;
		numParticles = 0;
	}

	/** Emits n particles at once */
	void Emit(int n)
	{
		for (int i = 0; i < numParticles; i++)
		{
			EmittedParticle *p = particles[i];
			if (!p->GetAlive() && n>0)
            {
				Vector3 v = velocity;

				v.x += (Util::Random() * 2 - 1) * velocityVar.x;
				v.y += (Util::Random() * 2 - 1) * velocityVar.y;
				v.z += (Util::Random() * 2 - 1) * velocityVar.z;

				p->Revive(position, life);
				p->SetVelocity(v);
				n--;
			}
		}
	}
	
	void AddParticle(EmittedParticle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
	}
};
#endif