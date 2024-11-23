all: clean compile link

clean:
	rm -f bin/*

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Settlement.o src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Action.o src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Facility.o src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Plan.o src/Plan.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Simulation.o src/Simulation.cpp

link:
	g++ -o bin/simulation bin/main.o bin/Settlement.o bin/Action.o bin/Auxiliary.o bin/Facility.o bin/Plan.o bin/SelectionPolicy.o bin/Simulation.o

run:
	./bin/simulation config_file.txt