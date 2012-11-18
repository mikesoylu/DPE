#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
	// Create the main rendering window
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Gorilla Game");
	App.setFramerateLimit(60);

	// Load the sprite image from a file
	sf::Texture Image;
	if (!Image.loadFromFile("assets/gorilla.png"))
		return EXIT_FAILURE;
	
        // Create the sprite
	sf::Sprite Sprite(Image);
	Sprite.setPosition(200.f, 100.f);
	Sprite.setScale(.5f, .5f);
	
	// Start game loop
	while (App.isOpen())
	{
		// Process events
		sf::Event event;
		while (App.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				App.close();
		}

		// Get elapsed time
		float ElapsedTime = 1.0/60.0;

		// Move the sprite
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  Sprite.move(-100 * ElapsedTime, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Sprite.move( 100 * ElapsedTime, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    Sprite.move(0, -100 * ElapsedTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Sprite.move(0,  100 * ElapsedTime);

		// Clear screen
		App.clear();

		// Display sprite in our window
		App.draw(Sprite);

		// Display window contents on screen
		App.display();
	}

	return EXIT_SUCCESS;
}
