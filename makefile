
Taxi: ./build/main.o ./build/taxi.o ./build/mundo.o ./build/mapa.o
	g++ -g -Wall ./build/main.o ./build/taxi.o ./build/mundo.o ./build/mapa.o -o Taxi -lsfml-graphics -lsfml-window -lsfml-system

./build/main.o: ./cpp/main.cpp
	g++ -c ./cpp/main.cpp -o ./build/main.o

./build/taxi.o: ./cpp/taxi.cpp ./hpp/taxi.hpp
	g++ -c ./cpp/taxi.cpp -o ./build/taxi.o

./build/mundo.o: ./cpp/mundo.cpp ./hpp/mundo.hpp
	g++ -c ./cpp/mundo.cpp -o ./build/mundo.o

./build/mapa.o: ./cpp/mapa.cpp ./hpp/mapa.hpp
	g++ -c ./cpp/mapa.cpp -o ./build/mapa.o

clean:
	rm ./build/*.o Taxi
