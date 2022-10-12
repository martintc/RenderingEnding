all:
	gcc -Wall -pedantic -g -lSDL2 -lGL -lGLEW -o renderer src/*.c

run:
	./renderer

clean:
	rm ./renderer
