
Taxi: main.o taxi.o mundo.o mapa.o
	g++ main.o taxi.o mundo.o mapa.o -o Taxi -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

taxi.o: taxi.cpp taxi.hpp
	g++ -c taxi.cpp

mundo.o: mundo.cpp mundo.hpp
	g++ -c mundo.cpp

mapa.o: mapa.cpp mapa.hpp
	g++ -c mapa.cpp

clean:
	rm *.o Taxi