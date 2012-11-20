#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "core/World.h"
#include "core/ParticleContactGenerator.h"
#include "core/RodContactGenerator.h"
#include "core/RodParticleContactGenerator.h"
#include "core/Spring.h"
#include "core/Util.h"

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
	// Create the main rendering window
	sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Awesome Game");
	app.setFramerateLimit(60);
	
	// Mouse
	sf::Vector2i mousePos;
	mousePos.x = 20;
	mousePos.y = 20;
	sf::Mouse::setPosition(mousePos, app);
	
	// Physics world
	World world;
	
	// Collision between particles
	ParticleContactGenerator *pcg = new ParticleContactGenerator(&world);
	world.AddContactGenerator(pcg);
	
	// Cable
	RodContactGenerator *rcg = new RodContactGenerator(&world);
	world.AddContactGenerator(rcg);

	// Particles vs walls and cable
	RodParticleContactGenerator *rpcg = new RodParticleContactGenerator(&world);
	world.AddContactGenerator(rpcg);

	// Infinite mass mouse particle
	Particle *mouseParticle = new Particle(mousePos.x, mousePos.y, 0, Util::INFINITE_MASS);
	mouseParticle->SetDamping(0);
	world.AddParticle(mouseParticle);
	
	// Mouse Spring
	Spring *mouseSpring = new Spring(mouseParticle, NULL, 0, 0.1, 100);
	world.AddForceGenerator(mouseSpring);
	
	// Particles for the cable
	Particle *lastCableParticle = NULL;
	for (int i = 0; i<60; i++)
	{
		Particle *p = new Particle(mouseParticle->GetPosition().x+(i+1)*10,  mouseParticle->GetPosition().y);
		
		if (NULL == lastCableParticle)
		{
			// add mouse spring
			mouseSpring->anchorB = p;
		} else
		{
			// Add particle to cable
			rcg->AddRod(new Rod(lastCableParticle, p, 10));
		}
		// set properties
		p->SetDamping(0.99);
		p->SetRadius(5);
		p->SetAcceleration(0, 100, 0);
				
		// Add particle to contact generators
		rpcg->AddParticle(p);
		pcg->AddParticle(p);
		
		// Add particle to physics world
		world.AddParticle(p);
		
		// set previous particle
		lastCableParticle = p;
	}
	
	// add walls
	Particle *topLeft = new Particle(0, 0, 0, Util::INFINITE_MASS);
	Particle *topRight = new Particle(WINDOW_WIDTH, 0, 0, Util::INFINITE_MASS);
	Particle *bottomLeft = new Particle(0, WINDOW_HEIGHT, 0, Util::INFINITE_MASS);
	Particle *bottomRight = new Particle(WINDOW_WIDTH, WINDOW_HEIGHT, 0, Util::INFINITE_MASS);
	
	world.AddParticle(topLeft);
	world.AddParticle(topRight);
	world.AddParticle(bottomLeft);
	world.AddParticle(bottomRight);

	rpcg->AddRod(new Rod(topLeft, topRight));
	rpcg->AddRod(new Rod(topRight, bottomRight));
	rpcg->AddRod(new Rod(bottomLeft, bottomRight));
	rpcg->AddRod(new Rod(topLeft, bottomLeft));
	
	// Start game loop
	while (app.isOpen())
	{
		// Process events
		sf::Event event;
		while (app.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
			{
				app.close();
			}
		}
		// get mouse position
		mousePos = sf::Mouse::getPosition(app);

		mouseParticle->SetPosition(mousePos.x, mousePos.y, 0);
		mouseParticle->SetVelocity(0, 0, 0);
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && lastCableParticle)
		{
			world.RemoveParticle(lastCableParticle);
			lastCableParticle = NULL;
		}
		
		// advance time
		for (int i = 0; i<20; i++)
		{
			world.Advance(1.0/1200.0);
		}
		// Clear screen
		app.clear();
		{
			// draw particles
			sf::Vertex vertices[world.numParticles];
			for (int i = 0; i<world.numParticles; i++)
			{
				Vector3 p = world.particles[i]->GetPosition();
				vertices[i].position.x = p.x;
				vertices[i].position.y = p.y;
			}
			app.draw(vertices, world.numParticles, sf::Points);
		}
		{
			// draw forces
			sf::Vertex vertices[world.numForces*2];
			int j = 0;
			for (int i = 0; i<world.numForces; i++, j+=2)
			{
				Spring *s = (Spring*)world.forces[i];
				
				Vector3 p1 = s->anchorA->GetPosition();
				Vector3 p2 = s->anchorB->GetPosition();
				
				vertices[j].position.x = p1.x;
				vertices[j].position.y = p1.y;
				vertices[j+1].position.x = p2.x;
				vertices[j+1].position.y = p2.y;
			}
			app.draw(vertices, world.numForces*2, sf::Lines);
		}
		// Display window contents on screen
		app.display();
	}

	return EXIT_SUCCESS;
}
