#ifndef RODCONTACT_H
#define	RODCONTACT_H

#include "Particle.h"
#include "Vector3.h"
#include "Rod.h"

class RodContact: public Contact
{
protected:
	Rod *rod;
	
public:
	RodContact(Rod *rod)
	{
		this->rod = rod;
	}
	
	virtual void Resolve(double dt)
	{
		Particle *particleA = rod->particleA;
		Particle *particleB = rod->particleB;
		
		Vector3 dd = particleA->GetPosition() - particleB->GetPosition();
		
		double min = rod->maxDist;
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

