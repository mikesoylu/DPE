#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "core/World.h"
#include "core/ParticleContactGenerator.h"
#include "core/RodContactGenerator.h"
#include "core/RodParticleContactGenerator.h"
#include "core/Spring.h"

#include <iostream>

int main()
{
	// Create the main rendering window
	sf::RenderWindow app(sf::VideoMode(800, 600, 32), "Awesome Game");
	app.setFramerateLimit(60);
	
	sf::Vector2f mousePos;
	
	World world;
	ParticleContactGenerator *cg = new ParticleContactGenerator(&world);
	for (int i = 0; i<30; i++)
	{
		Particle *p = new Particle(i*20, 300);
		
		if (0 == i)
		{
			p->SetMass(Util::INFINITE_MASS);
		} else if (i<30-3)
		{
			p->SetVelocity((Util::Random() - 0.5)*100, (Util::Random() - 0.5)*100, 0.0);
			cg->AddParticle(p);
		} else if (i>30-3)
		{
			p->SetMass(Util::INFINITE_MASS);
		}
		p->SetDamping(0.9);
		p->SetRadius(5);
		p->SetAcceleration(0, 90.8, 0);
		world.AddParticle(p);
	}
	world.AddContactGenerator(cg);
	
	// make rope
	RodContactGenerator *rcg = new RodContactGenerator(&world);
	for (int i = 1; i<world.numParticles-2; i++)
	{
		rcg->AddRod(new Rod(world.particles[i],world.particles[i+1],10));
	}
	world.AddContactGenerator(rcg);
	
	// add mouse joint
	world.AddForceGenerator(new Spring(world.particles[0], world.particles[1], 0));
	
	// add walls
	world.particles[world.numParticles-2]->SetAcceleration(0,0,0);
	world.particles[world.numParticles-1]->SetAcceleration(0,0,0);
	world.particles[world.numParticles-2]->SetPosition(20,300,0);
	world.particles[world.numParticles-1]->SetPosition(780,500,0);
	
	world.particles[world.numParticles-3]->SetRadius(30);

	RodParticleContactGenerator *rpcg = new RodParticleContactGenerator(&world);
	rpcg->AddParticle(world.particles[world.numParticles-3]);
	rpcg->AddRod(new Rod(world.particles[world.numParticles-2], world.particles[world.numParticles-1]));
	world.AddContactGenerator(rpcg);
	
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
				
			} else if (event.type == sf::Event::MouseMoved)
			{
				mousePos.x = event.mouseMove.x;
				mousePos.y = event.mouseMove.y;
			}
		}
		
		world.particles[0]->SetPosition(mousePos.x, mousePos.y, 0);
		world.particles[0]->SetVelocity(0, 0, 0);
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
