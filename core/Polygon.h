/* 
 * File:   Polygon.h
 * Author: mikesoylu
 *
 * Created on 21 Kasım 2012 Çarşamba, 00:19
 */

#ifndef POLYGON_H
#define	POLYGON_H

#include "Particle.h"


class Polygon
{
protected:
	static const int MAX_PARTICLES = 8;
	Particle *particles[MAX_PARTICLES];
	int numParticles;
	
public:
	Polygon()
	{
		numParticles = 0;
	}
	
	void AddParticle(Particle *p)
	{
		if (numParticles<MAX_PARTICLES)
			particles[numParticles++] = p;
	}
	
	double GetRotation()
	{
		if (numParticles>2)
		{
			Vector3 dd = particles[0]->GetPosition() - GetCenter();
			return atan2(dd.y, dd.x)+M_PI/numParticles;
		}
		return 0;
	}
	
	Vector3 GetCenter() const
	{
		Vector3 c;
		for (int i = 0; i<numParticles; i++)
			c += particles[i]->GetPosition();
		
		c *= 1.0/numParticles;
		
		return c;
	}
};

#endif	/* POLYGON_H */

