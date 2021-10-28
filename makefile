Taxi: ./build/main.o ./build/taxi.o ./build/mundo.o ./build/mapa.o ./build/nodo.o
	g++ -g -Wall ./build/main.o ./build/taxi.o ./build/mundo.o ./build/mapa.o ./build/nodo.o -o Taxi -lsfml-graphics -lsfml-window -lsfml-system

./build/main.o: ./cpp/main.cpp
	g++ -c ./cpp/main.cpp -o ./build/main.o

./build/taxi.o: ./cpp/taxi.cpp ./hpp/taxi.hpp
	g++ -c ./cpp/taxi.cpp -o ./build/taxi.o
 
./build/mundo.o: ./cpp/mundo.cpp ./hpp/mundo.hpp
	g++ -c ./cpp/mundo.cpp -o ./build/mundo.o

./build/mapa.o: ./cpp/mapa.cpp ./hpp/mapa.hpp
	g++ -c ./cpp/mapa.cpp -o ./build/mapa.o

./build/nodo.o: ./cpp/nodo.cpp ./hpp/nodo.hpp
	g++ -c ./cpp/nodo.cpp -o ./build/nodo.o

clean:
	rm ./build/*.o Taxi
