LIBS=-lm -lSDL2 -lGL -lGLEW -L/usr/local/lib -lcglm
INCLUDE=-I/usr/local/include

all:
	gcc -Wall -pedantic -g $(INCLUDE) $(LIBS) -o renderer src/*.c

run:
	./renderer

clean:
	rm ./renderer
