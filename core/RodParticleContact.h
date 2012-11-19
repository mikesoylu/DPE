#ifndef RODPARTICLECONTACT_H
#define	RODPARTICLECONTACT_H

#include "Particle.h"
#include "Vector3.h"
#include "Rod.h"

class RodParticleContact: public Contact
{
protected:
	Rod *rod;
	Particle *particle;
public:
	RodParticleContact(Rod *rod, Particle *particle)
	{
		this->rod = rod;
		this->particle = particle;
	}
	
	virtual void Resolve(double dt)
	{
		Vector3 l = rod->particleA->GetPosition()-rod->particleB->GetPosition();
		l.Normalize();
		Vector3 d = particle->GetPosition()-rod->particleB->GetPosition();
		double dot = d*l;
		double cross = (d%l).Magnitude();
		
		double totalRod = rod->particleA->GetMass() + rod->particleB->GetMass();
		double total = totalRod + particle->GetMass();

		Vector3 dsp = l*dot - d; // displacement
		dsp.Normalize();
		dsp *= cross - 0.01 - particle->GetRadius(); // add some epsilon
		
		Vector3 pp = particle->GetPosition();
		Vector3 pv = particle->GetVelocity();
		
		Vector3 rp1p = rod->particleA->GetPosition();
		Vector3 rp1v = rod->particleA->GetVelocity();
		
		Vector3 rp2p = rod->particleB->GetPosition();
		Vector3 rp2v = rod->particleB->GetVelocity();
		
		pp += dsp * (totalRod / total);
		pv += dsp * (totalRod / total / dt);
		
		rp1p += dsp * (particle->GetMass() / total);
		rp1v += dsp * (-particle->GetMass() / total / dt);
		
		rp2p += dsp * (particle->GetMass() / total);
		rp2v += dsp * (-particle->GetMass() / total / dt);
		
		particle->SetPosition(pp);
		particle->SetVelocity(pv);
		
		rod->particleA->SetPosition(rp1p);
		rod->particleA->SetVelocity(rp1v);
		
		rod->particleB->SetPosition(rp2p);
		rod->particleB->SetVelocity(rp2v);
	}
};
#endif

