all: clean compile link run

run: bin/SPLand
	bin/SPLand config_file.txt

compile: 
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Simulation.o src/Simulation.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
link:
	g++ -o bin/SPLand bin/Auxiliary.o bin/Simulation.o bin/main.o

clean: 
	rm -f bin/*