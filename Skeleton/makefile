# Default target
all: clean compile_main compile_settlement link run

# Clean up the generated files
clean:
	rm -f bin/*

# Compile the main source file
compile_main:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp

# Compile the Settlement source file
compile_settlement:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Settlement.o src/Settlement.cpp

# Link object files to create the final executable
link: compile_main compile_settlement
	g++ -o bin/simulation bin/main.o bin/Settlement.o

# Run the program
run:
	./bin/simulation
