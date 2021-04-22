functions.o: functions.cpp functions.h
	g++ -c $<

prints.o: prints.cpp prints.h
	g++ -c $<

board.o: board.cpp board.h functions.h
	g++ -c $<

main.o: main.cpp board.h functions.h prints.h
	g++ -c $<

main: main.o functions.o prints.o board.o
	g++ -pedantic-errors -std=c++11 $^ -o $@

clean:
	rm -f main.o functions.o prints.o board.o savefile.txt main

.PHONY: clean