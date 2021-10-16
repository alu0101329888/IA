#include <SFML/Graphics.hpp>
#include "mapa.hpp"
#include "mundo.hpp"
#include "taxi.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 216), "Mapa");

    // define the level with an array of tile indices
    const int level[] =
    {
        1, 2, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1,
        1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1,
        1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
        0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
    };

    // create the tilemap from the level definition
    Mapa map;
    if (!map.load("casillas.png", sf::Vector2u(32, 32), level, 16, 8))
        return -1;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}




int main(int argc, char *argv[]) {

  int dimX, dimY, taxiX, taxiY, destinoX, destinoY, numObstaculos;
  std::string opcion;
  Mundo MainWorld;
  
  //Menu
  if (argc != 2) {
    
    std::cout << "No se ha especificado un fichero del cual leer, por tanto se introduciran los obstaculos de manera aleatoria." << std::endl;
    std::cout << "Introduzca las dimensiones de la matriz X*Y" << std::endl;
    while (dimX <= 0 || dimY <= 0) {
      std::cout << "Dimension X: ";
      std::cin >> dimX;
      std::cout << "Dimension Y: ";
      std::cin >> dimY;
      if (dimX <= 0 || dimY <= 0) {
        std::cout << "El valor no puede ser menor o igual que cero" << std::endl;
      }
    }

    MainWorld.Resize(dimX, dimY);
    
    std::cout << "Introduzca el numero de obstaculos a colocar o R para elegir uno aleatorio: ";
    std::cin >> opcion;

    while (opcion != "R" && std::stoi(opcion) < 0 || std::stoi(opcion) > ((dimX * dimY) - 2)) {
        std::cout << "Cantidad de obstaculos no permitida, escoja otra cantidad o seleccione R para poner un numero aleatorio" << std::endl;
        std::cin >> opcion;
    }

    if (opcion == "R") {
      numObstaculos = rand() % dimX*dimY + 0;
      std::cout << "Elegidos " << numObstaculos << "nº de obstaculos" << std::endl;
      //MainWorld.Random((rand() % dimX*dimY + 0)); //genera un numero aleatorio entre 0 y dimX*dimY
    }
    else {
      numObstaculos = std::stoi(opcion);
      std::cout << "Elegidos " << numObstaculos << "nº de obstaculos" << std::endl;
    }

    MainWorld.PrintMundo();

    while(taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_)) {
      std::cout << "Introduzca la coordenada en donde se situara el taxi" << std::endl << "Posicion del taxi X: ";
      std::cin >> taxiX;
      std::cout << "Posicion del taxi Y: ";
      std::cin >> taxiY;
      if (taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY) {
        std::cout << "Esa casilla no existe o se encuentra obstaculizada" << std::endl;
      }
    }

    while(destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_)) {
      std::cout << "Introduzca la coordenada en donde se situara el destino" << std::endl << "Posicion del destino X: ";
      std::cin >> destinoX;
      std::cout << "Posicion del destino Y: ";
      std::cin >> destinoY;
      if (destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY)) {
        std::cout << "Esa casilla no existe, se encuentra obstaculizada o es la de inicio" << std::endl;
      }
    }
  }

  else {
    std::ifstream Archivo;
    Archivo.open(argv[1]);
  
    if(Archivo.fail()) {
      std::cout << "Error al abrir el archivo" << argv[1] << std::endl;
      return -1;
    }

    MainWorld.Load(Archivo);
 
    Archivo.close();
  }
  
  Taxi MainTaxi(MainWorld, taxiX, taxiY, destinoX, destinoY);

  std::vector<std::vector<int>> Camino = MainTaxi.CaminoMinimo();
  MainTaxi.MovDer();
  
  //algoritmo



  return 0;
}