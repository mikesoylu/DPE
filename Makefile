make:
	g++ MainGame.cpp -o bin/Main -lsfml-graphics -lsfml-window
debug:
	g++ MainGame.cpp -o bin/Main -DDEBUG -lsfml-graphics -lsfml-window
clean:
	rm Main