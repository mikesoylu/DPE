#ifndef FORCEGENERATOR_H
#define	FORCEGENERATOR_H

class Particle;

class ForceGenerator
{
public:
    virtual void ApplyForces() = 0;
	virtual bool RemoveParticle(Particle *p) = 0;
};

#endif	/* FORCEGENERATOR_H */

