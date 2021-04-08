functions.o: functions.cpp functions.h
	g++ -c $<

prints.o: prints.cpp prints.h
	g++ -c $<

main.o: main.cpp functions.h
	g++ -c $<

main: main.o functions.o prints.o
	g++ -pedantic-errors -std=c++11 $^ -o $@

clean:
	rm -f main.o functions.o prints.o savefile.txt main

.PHONY: clean