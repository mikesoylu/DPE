#ifndef EMITTER_H
#define EMITTER_H

#include <cmath>
#include <vector>
#include "EmittedParticle.h"
#include "Vector3.h"

using std::vector;

class Emitter
{
protected:
	vector<EmittedParticle> particles;
	
	double life;
	double lifeVar;

	Vector3 position;
	Vector3 velocity;
	Vector3 velocityVar;

public:
	Emitter(Vector3 position, Vector3 velocity, double life, Vector3 velocityVar, double lifeVar)
	{
		this->position = position;
		this->velocity = velocity;
		this->velocityVar = velocityVar;

		this->life = life;
		this->lifeVar = lifeVar;
	}

	/** Emits n particles at once */
	void Emit(int n)
	{
		// shal we skip looking for dead particles
		bool skip = false;

		for (int i = 0; i < n; i++)
		{
			bool found = false;
			if (!skip)
				for (int j = 0; j < particles.Size(); j++)
					if (!particles[j].GetAlive())
					{
						particles[j].Revive(position, life + Utils::Random() * liveVar);

						Vector3 v = velocity;
						v += velocityVar * Utils::Random() * 2 - velocityVar;
						particles[j].velocity = v;

						found = true;
					} 

			if (!found)
			{
				// we coldn't find any dead so stop looking
				skip = true;
				EmittedParticle p(position, life + Utils::Random() * liveVar);

				Vector3 v = velocity;
				v += velocityVar * Utils::Random() * 2 - velocityVar;
				p.velocity = v;

				particles.push_back(p);
			}
		}

		/** Integrates all particles */
		void Integrate(double dt)
		{
			for (int i = 0; i < particles.Size(); i++)
			{
				particles[i].Integrate(dt);
			}
		}
	};
