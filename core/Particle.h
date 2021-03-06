#ifndef PARTICLE_H
#define PARTICLE_H


#include <iostream>
#include <cmath>
#include "Vector3.h"
#include "Util.h"

using std::cout;
using std::endl;

class Particle
{
protected:
	Vector3 position, velocity, acceleration, forceAccum;
	double damping, mass, invMass, radius;
	
public:
	Particle(double x = 0, double y = 0, double z = 0, double m = 1, double r = 10)
	{
		position = Vector3(x,y,z);
		mass = m;
		invMass = 1.0/m;
		damping = 1;
		radius = r;
	}
	/* gets */
	Vector3 GetPosition() const
	{
		return position;
	}

	Vector3 GetVelocity() const
	{
		return velocity;
	}

	Vector3 GetAcceleration() const
	{
		return acceleration;
	}

	double GetMass() const
	{
		return mass;
	}

	double GetDamping() const
	{
		return damping;
	}

	double GetRadius() const
	{
		return radius;
	}
	
	/* sets */

	void SetPosition(Vector3 &p)
	{
		if (p.IsValid())
		{
			position.x = p.x;
			position.y = p.y;
			position.z = p.z;
		}
	}

    void SetPosition(double x, double y, double z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void SetVelocity(Vector3 &v)
	{
		if (v.IsValid())
		{
			velocity.x = v.x;
			velocity.y = v.y;
			velocity.z = v.z;
		}
	}

	void SetVelocity(double x, double y, double z)
	{
		velocity.x = x;
		velocity.y = y;
		velocity.z = z;
	}

	void SetAcceleration(double x, double y, double z)
	{
		acceleration.x = x;
		acceleration.y = y;
		acceleration.z = z;
	}

	void SetMass(double m)
	{
		if (m <= 0.001)
		{
			mass = m;
			invMass = 1.0/m;
		}
	}

	void SetDamping(double d)
	{
		damping = d;
	}

	void SetRadius(double r)
	{
		radius = r;
	}
	
	/** Clear forces */
	void ClearForces()
	{
		forceAccum *= 0.0;
	}

	/** Applies force to body */
	void ApplyForce(Vector3 force)
	{
		forceAccum += force;
	}
	
	/** Euler integration */
	virtual void Integrate(double dt)
	{
		if (forceAccum.IsValid() && position.IsValid() && velocity.IsValid() && acceleration.IsValid())
		{
			position += velocity*dt;
			velocity += (acceleration+(forceAccum*invMass))*dt;
			velocity *= pow(damping, dt);
		}
		ClearForces();
	}

	/** print */
	void Print() const
	{
		cout << '(' << position.x << ',' << position.y << ',' << position.z << ')' << endl;
	}
};

#endif
