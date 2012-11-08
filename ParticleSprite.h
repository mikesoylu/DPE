#ifndef PARTICLE_SPRITE_H
#define PARTICLE_SPRITE_H

#include <SFML/Graphics.hpp>
#include "core/Particle.h"

using sf::Sprite;
using sf::Texture;

class ParticleSprite:public Sprite, public Particle
{
public:
	ParticleSprite(Texture& img) : Particle(), Sprite(img) {}

	void Update(double dt)
	{
	    Integrate(dt);
	    // update sfml position
	    setPosition(position.x, position.y);
	}
};

#endif
