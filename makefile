P3.out: Proj3app.o Maze.o
	g++ -g -o P3.out Proj3app.o Maze.o

Proj3app.o: Proj3app.cpp Maze.h
	g++ -g -c Proj3app.cpp

Maze.o: Maze.cpp Maze.h
	g++ -g -c Maze.cpp

clean:
	rm *.o P3.out

run : ./P3.out
	clear
	./P3.out

submit : Proj3app.cpp Maze.h Maze.cpp makefile README.txt
	rm -rf fewellP3
	mkdir fewellP3
	cp Proj3app.cpp fewellP3
	cp Maze.h fewellP3
	cp Maze.cpp fewellP3
	cp makefile fewellP3
	cp README.txt fewellP3
	tar cfvz fewellP3.tgz fewellP3
	cp fewellP3.tgz ~tiawatts/cs215drop
