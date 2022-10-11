all:
	gcc -Wall -pedantic -g -lSDL2 -lGL -lGLEW -o triangle src/*.c

run:
	./triangle

clean:
	rm ./triangle
