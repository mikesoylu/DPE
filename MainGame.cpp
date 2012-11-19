#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "core/World.h"
#include "core/Util.h"
#include "core/Spring.h"
#include "core/RodContactGenerator.h"
#include "core/ParticleContactGenerator.h"

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
		Particle *p = new Particle(i+400, 300);
		
		if (0 == i)
		{
			p->SetMass(Util::INFINITE_MASS);
		} else
		{
			p->SetVelocity((Util::Random() - 0.5)*100, (Util::Random() - 0.5)*100, 0.0);
			cg->AddParticle(p);
		}
		p->SetDamping(0.9);
		p->SetRadius(5);
		p->SetAcceleration(0, 100, 0);
		world.AddParticle(p);
	}
	world.AddContactGenerator(cg);
	
	for (int i = 1; i<world.numParticles-1; i++)
	{
		RodContactGenerator *cg = new RodContactGenerator(&world);
		cg->particleA = world.particles[i];
		cg->particleB = world.particles[i+1];
		cg->maxDist = 10;
		world.AddContactGenerator(cg);
	}
	world.AddForce(new Spring(world.particles[0], world.particles[1], 0));
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
		for (int i = 0; i<10; i++)
		{
			world.Advance(1.0/600.0);
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
