#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include "Vector3.h"

using std::cout;
using std::endl;

class Particle
{
protected:
	Vector3 position, velocity, acceleration, forceAccum;
	double damping, mass, invMass;
public:
	Particle(double x = 0, double y = 0, double z = 0, double m = 1)
	{
		position = Vector3(x,y,z);
		mass = m;
		invMass = 1.0/m;
		damping = 1;
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
	/* sets */
    void SetPosition(double x, double y, double z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void SetPosition(Vector3 p)
	{
		position.x = p.x;
		position.y = p.y;
		position.z = p.z;
	}

	void SetVelocity(Vector3 v)
	{
		velocity.x = v.x;
		velocity.y = v.y;
		velocity.z = v.z;
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
		mass = m;
		invMass = 1.0/m;
	}

	void SetDamping(double d)
	{
		damping = d;
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
		if (0.0 == invMass)
		{
			cout << "ERROR:Mass is zero" << endl;
		}
		position += velocity*dt;
		velocity += (acceleration+(forceAccum*invMass))*dt;
		velocity *= pow(damping, dt);
		ClearForces();
	}

	/** print */
	void Print() const
	{
		cout << '(' << position.x << ',' << position.y << ',' << position.z << ')' << endl;
	}
};

#endif
