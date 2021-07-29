output: game.o display.o creatures.o
	g++ game.o terminal-display.o player.o enemy.o -o m 

game.o: game.cpp
	g++ -c game.cpp

display.o: terminal-display.cpp terminal-display.h
	g++ -c -lfmt terminal-display.cpp

creatures.o: player.cpp enemy.cpp creature.cpp creatures.h
	g++ -c player.cpp enemy.cpp creature.cpp

clean:
	rm *.o m