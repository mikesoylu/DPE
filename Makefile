all:
	g++ MainGame.cpp -o bin/Main -DDEBUG -g -lsfml-graphics -lsfml-window
debug:
	g++ MainGame.cpp -o bin/Main -DDEBUG -g -lsfml-graphics -lsfml-window
clean:
	rm bin/Main.exe