functions.o: functions.cpp functions.h
	g++ -c $<

main.o: main.cpp functions.h
	g++ -c $<

main: main.o functions.o
	g++ -pedantic-errors -std=c++11 $^ -o $@

clear:
	rm -f main.o functions.o main

.PHONY: clear