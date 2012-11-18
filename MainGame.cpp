#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "core/World.h"
#include "core/Util.h"
#include "core/Spring.h"

#include <iostream>

int main()
{
	// Create the main rendering window
	sf::RenderWindow app(sf::VideoMode(800, 600, 32), "Awesome Game");
	app.setFramerateLimit(60);
	
	World world;
	
	for (int i = 0; i<20; i++)
	{
		Particle *p = new Particle(i, 300);
		
		if (0 == i)
		{
			p->SetMass(INFINITY);
		} else
		{
			p->SetVelocity((Util::Random() - 0.5)*100,
							(Util::Random() - 0.5)*100,
							(Util::Random() - 0.5)*100);
		}
		p->SetDamping(0.5);
		world.AddParticle(p);
	}
	for (int i = 0; i<world.numParticles-1; i++)
	{
		Spring *s = new Spring(world.particles[i], world.particles[i+1], 2, 1, 50);
		world.AddForce(s);
	}
	
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
				world.particles[0]->SetPosition(event.mouseMove.x, event.mouseMove.y, 0);
			}
		}

		// advance time
		world.Advance(1.0/60.0);
		
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
