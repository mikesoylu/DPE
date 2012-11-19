#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"
#include "Vector3.h"
#include "ForceGenerator.h"
#include <iostream>
#include <cmath>

class Spring:public ForceGenerator
{
protected:
	double damping;
	double springConstant;
	double restDistance;
public:
	Particle *anchorA;
	Particle *anchorB;
	
	Spring(Particle *A, Particle *B, double restDistance, double damping = 0.2, double constant = 50)
	{
		this->anchorA = A;
		this->anchorB = B;
		this->damping = damping;
		this->springConstant = constant;
		this->restDistance = restDistance;
	}

	/** sets */
	void SetDamping(double val)
	{
		damping = val;
	}
	void SetSpringConstant(double val)
	{
		springConstant = val;
	}

	/** gets */
	double GetDamping()
	{
		return damping;
	}

	double GetSpringConstant()
	{
		return springConstant;
	}
	
	virtual bool RemoveParticle(Particle *p)
	{
		if (anchorA == p || anchorB == p)
		{
			return true;
		}
		return false;
	}
	
	/** Apply spring forces to anchors */
	virtual void ApplyForces()
	{
		Vector3 dd = anchorB->GetPosition() - anchorA->GetPosition();
		double mag = dd.Magnitude() - restDistance;
		dd.Normalize();

		// spring force
		anchorA->ApplyForce(dd * springConstant * mag);
		anchorB->ApplyForce(dd * springConstant * -mag);

		// damping force
		Vector3 vd = anchorA->GetVelocity() - anchorB->GetVelocity();
		anchorA->ApplyForce(vd * -damping);
		anchorB->ApplyForce(vd * damping);
	}
};

#endif
