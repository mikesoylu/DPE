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

		for (int i = 0; i < n; i++)
		{
            // we coldn't find any dead so stop looking
            EmittedParticle p(this->position, life + Util::Random() * lifeVar);

            Vector3 v = velocity;

            v.x += (Util::Random() * 2 - 1) * velocityVar.x;
            v.y += (Util::Random() * 2 - 1) * velocityVar.y;
            v.z += (Util::Random() * 2 - 1) * velocityVar.z;

            p.SetVelocity(v);
            particles.push_back(p);
		}
	}

    /** gets */
	int GetNumParticles() const
	{
	    return particles.size();
	}

	EmittedParticle &GetParticle(int i)
	{
	     return particles[i];
	}

    /** sets */
    void SetPosition(Vector3 p)
    {
        this->position.x = p.x;
        this->position.y = p.y;
        this->position.z = p.z;
    }

    /** Integrates all particles */
    void Update(double dt)
    {
        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].Integrate(dt);
        }
    }
};
#endif
