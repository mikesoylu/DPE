#ifndef EMITTED_PARTICLE_H
#define EMITTED_PARTICLE_H

#include <cmath>
#include "Particle.h"
#include "Util.h"

using std::vector;

class EmittedParticle: public Particle
{
protected:
	double life;
	bool alive;
public:
	EmittedParticle(Vector3 position, double life = 1)
	{
		Particle(position.x, position.y, position.z);
		this->life = life;
		alive = true;
	}
	EmittedParticle(double x = 0, double y = 0, double z = 0, double life = 1)
	{
		Particle(x, y, z);
		this->life = life;
		alive = true;
	}

	void Revive(Vector3 position, double life = 1)
	{
		Particle(position.x, position.y, position.z);
		this->life = life;
		alive = true;
	}

	/* gets **/
	double GetLife() const
	{
		return life;
	}

	bool GetAlive() const
	{
		return alive;
	}

	/* sets **/
	void SetLife()
	{
		this->life = life;
	}

	void SetAlive(bool value)
	{
		this->alive = value;
	}

	/** Euler integration */
	virtual void Integrate(double dt)
	{
		if (alive)
			return;

		Particle::Integrate(dt);
		life -= dt;

		if (life <= 0.0)
		{
			alive = false;
		}
	}
};

#endif
