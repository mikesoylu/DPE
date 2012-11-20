#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "core/World.h"
#include "core/ParticleContactGenerator.h"
#include "core/RodContactGenerator.h"
#include "core/RodParticleContactGenerator.h"
#include "core/Spring.h"
#include "core/Util.h"

#include <iostream>
#include <vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Physics world
World world;
Spring *clampSpring = NULL;

void collide(Contact *c)
{
	ParticleContact *pc = (ParticleContact *)c;
	if (NULL == clampSpring)
	{
		clampSpring = new Spring(pc->particleA, pc->particleB, 10, 0.5, 100);
		world.AddForceGenerator(clampSpring);
	}
}

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
	
	// Collision between triangle particles cable tip
	ParticleContactGenerator *pcg = new ParticleContactGenerator(&world);
	pcg->contactCallback = *collide;
	world.AddContactGenerator(pcg);
	
	// Collision between triangle rods cable tip
	RodParticleContactGenerator *trpcg = new RodParticleContactGenerator(&world);
	world.AddContactGenerator(trpcg);
	
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
	Spring *mouseSpring = new Spring(mouseParticle, NULL, 0, 0.99, 50);
	world.AddForceGenerator(mouseSpring);
	
	// particles for payload
	{
		double x = WINDOW_WIDTH/2;
		double y = WINDOW_HEIGHT/2;
		double l = 100.0;
		double r = l * 0.5 / 0.57735026919;
		Particle *tri[3];
		for (int i = 0; i<3; i++)
		{
			Particle *p = new Particle(x + r*cos(M_PI*2*(i/3.0)),  y + r*sin(M_PI*2*(i/3.0)));
			// set properties
			p->SetDamping(0.5);
			p->SetRadius(5);
			p->SetMass(20);
			p->SetAcceleration(0, 100, 0);
			// Add particle to contact generators
			rpcg->AddParticle(p);
			pcg->AddParticle(p);

			// Add particle to physics world
			world.AddParticle(p);
			tri[i] = p;
		}
		
		// these allow collision with particles
		trpcg->AddRod(new Rod(tri[0], tri[1], l));
		trpcg->AddRod(new Rod(tri[1], tri[2], l));
		trpcg->AddRod(new Rod(tri[2], tri[0], l));
		
		// these hold the triangle together
		rcg->AddRod(new Rod(tri[0], tri[1], l, true));
		rcg->AddRod(new Rod(tri[1], tri[2], l, true));
		rcg->AddRod(new Rod(tri[2], tri[0], l, true));

	}
	// Particles for the cable
	std::vector<Particle *> cable;
	for (int i = 0; i<2; i++)
	{
		Particle *p = new Particle(mouseParticle->GetPosition().x+(i+1)*10,  mouseParticle->GetPosition().y);
		
		if (i == 0)
		{
			// add mouse spring
			mouseSpring->anchorB = p;
		} else
		{
			// Add particle to cable
			rcg->AddRod(new Rod(cable[i-1], p, 4));
			trpcg->AddParticle(p);
			pcg->AddParticle(p);
		}
		// set properties
		p->SetDamping(0.5);
		p->SetRadius(5);
		p->SetAcceleration(0, 100, 0);
				
		// Add particle to contact generators
		rpcg->AddParticle(p);

		// Add particle to physics world
		world.AddParticle(p);
		
		// set previous particle
		cable.push_back(p);
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
		
		// add to cable
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && cable.size() > 2)
		{
			mouseSpring->anchorB = cable[1];
			world.RemoveParticle(cable[0]);
			cable.erase(cable.begin());
		}
		// release from cable
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && clampSpring)
		{
			world.RemoveForceGenerator(clampSpring);
			clampSpring = NULL;
		}
		
		// add to cable
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Particle *p = new Particle(cable[1]->GetPosition().x,  cable[1]->GetPosition().y);

			// Add particle to cable
			rcg->RemoveParticle(cable[1]);
			rcg->AddRod(new Rod(cable[1], p, 4));
			rcg->AddRod(new Rod(cable[0], p, 4));
			if (cable.size() > 2)
				rcg->AddRod(new Rod(cable[1], cable[2], 4));

			// set properties
			p->SetDamping(0.5);
			p->SetRadius(5);
			p->SetAcceleration(0, 100, 0);

			// Add particle to contact generators
			rpcg->AddParticle(p);

			// Add particle to physics world
			world.AddParticle(p);

			// set previous particle
			cable.insert(cable.begin()+1,p);
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
