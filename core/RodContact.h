#ifndef RODCONTACT_H
#define	RODCONTACT_H

#include "Particle.h"
#include "Vector3.h"

class RodContact: public Contact
{
protected:
	Particle *particleA;
	Particle *particleB;
	
	double maxDistance;
	
public:
	RodContact(Particle *pA, Particle *pB, double maxDistance)
	{
		particleA = pA;
		particleB = pB;
		this->maxDistance = maxDistance;
	}
	
	virtual void Resolve(double dt)
	{
		Vector3 dd = particleA->GetPosition() - particleB->GetPosition();
		
		double min = maxDistance;
		min -= dd.Magnitude();
		
		Vector3 pa = particleA->GetPosition();
		Vector3 pb = particleB->GetPosition();
		
		Vector3 va = particleA->GetVelocity();
		Vector3 vb = particleB->GetVelocity();
		
		dd.Normalize();
		double total = particleA->GetMass() + particleB->GetMass();
		
		pa += dd * min * (particleB->GetMass() / total);
		pb += dd * min * (-particleA->GetMass() / total);
		va += dd * min * (particleB->GetMass() / total / dt);
		vb += dd * min * (-particleA->GetMass() / total / dt);
		
		particleA->SetPosition(pa);
		particleB->SetPosition(pb);
		particleA->SetVelocity(va);
		particleB->SetVelocity(vb);
	}
};

#endif

