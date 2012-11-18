#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"
#include "Vector3.h"
#include <iostream>
#include <cmath>

class Spring
{
protected:
	Particle *anchorA;
	Particle *anchorB;
	double damping;
	double springConstant;
	double restDistance;
public:
	Spring(Particle *A, Particle *B, double restDistance, double damping = 0.2, double constant = 10)
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

	/** Apply spring forces to anchors */
	void ApplyForces()
	{
		Vector3 dd = anchorB->GetPosition() - anchorA->GetPosition();
		double mag = dd.Magnitude() - restDistance;
		dd.Normalize();

		// spring force
		anchorA->ApplyForce(dd * springConstant * mag);
		anchorB->ApplyForce(dd * springConstant * -mag);

		// damping force
		anchorA->ApplyForce(dd * anchorA->GetVelocity() * damping);
		anchorB->ApplyForce(dd * anchorB->GetVelocity() * damping);
	}
};

#endif
