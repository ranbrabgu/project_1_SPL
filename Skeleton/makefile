# Default target
all: clean compile_main compile_settlement compile_Action compile_Auxiliary compile_Facility compile_Plan compile_SelectionPolicy compile_Simulation link_main_settlement link_main_Action link_main_Auxiliary link_main_Facility link_main_Plan link_main_SelectionPolicy link_main_Simulation run

# Clean up the generated files
clean:
	rm -f bin/*

# Compile the main source file
compile_main:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp

# Compile the Settlement source file
compile_settlement:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Settlement.o src/Settlement.cpp

# Compile the Action source file
compile_Action:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Action.o src/Action.cpp

# Compile the Auxiliary source file
compile_Auxiliary:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Auxiliary.o src/Auxiliary.cpp

# Compile the Facility source file
compile_Facility:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Facility.o src/Facility.cpp

# Compile the Plan source file
compile_Plan:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Plan.o src/Plan.cpp

# Compile the SelectionPolicy source file
compile_SelectionPolicy:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/SelectionPolicy.o src/SelectionPolicy.cpp

# Compile the Simulation source file
compile_Simulation:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Simulation.o src/Simulation.cpp



# Link object files to create the final executable
link_main_settlement: compile_main compile_settlement
	g++ -o bin/simulation bin/main.o bin/Settlement.o

link_main_Action: compile_main compile_Action
	g++ -o bin/simulation bin/main.o bin/Action.o

link_main_Auxiliary: compile_main compile_Auxiliary
	g++ -o bin/simulation bin/main.o bin/Auxiliary.o

link_main_Facility: compile_main compile_Facility
	g++ -o bin/simulation bin/main.o bin/Facility.o

link_main_Plan: compile_main compile_Plan
	g++ -o bin/simulation bin/main.o bin/Plan.o

link_main_SelectionPolicy: compile_main compile_SelectionPolicy
	g++ -o bin/simulation bin/main.o bin/SelectionPolicy.o

link_main_Simulation: compile_main compile_Simulation
	g++ -o bin/simulation bin/main.o bin/Simulation.o

# Run the program
run:
	./bin/simulation
