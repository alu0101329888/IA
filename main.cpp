#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "mundo.hpp"
#include "taxi.hpp"

int main(int argc, char *argv[]) { 

  int dimX, dimY;
  int taxiX, taxiY;
  int destinoX, destinoY;
  std::string opcion;

  if (argc != 2) {

    std::cout << "Introduzca las dimensiones de la matiz X*Y" << std::endl << "Dimension X: ";
    std::cin >> dimX;
    std::cout << "Dimension Y: ";
    std::cin >> dimY;
    
    Mundo MainWorld(dimX, dimY);
    std::cout << "Introduzca el numero de obstaculos a colocar o R para elegir uno aleatorio: ";
    std::cin >> opcion;

    if (opcion == "R") {
      MainWorld.Random((rand() % dimX*dimY + 0)); //genera un numero aleatorio entre 0 y dimX*dimY
    }
    else {
      if (MainWorld.Random(std::stoi(opcion)) == -1) {
        std::cout << "¡Hay demasiados obstaculos!" << std::endl;
        return -1;
      }
    }

    MainWorld.PrintMundo();
    
    std::cout << "Introduzca la coordenada en donde se situara el taxi" << std::endl << "Dimension del taxi X: ";
    std::cin >> taxiX;
    std::cout << "Dimension del taxi Y: ";
    std::cin >> taxiY;

    while (MainWorld.Status(taxiX, taxiY) == _OBSTACULO) {
      std::cout << "Esa casilla se encuentra bloqueada por un obstaculo, elija otra" << std::endl;
      std::cout << "Posicion del taxi X: ";
      std::cin >> taxiX;
      std::cout << "Posicion del taxi Y: ";
      std::cin >> taxiY;
    }

    std::cout << "Introduzca la coordenada en donde se situara el destino" << std::endl << "Dimension del destino X: ";
    std::cin >> destinoX;
    std::cout << "Posicion del destino Y: ";
    std::cin >> destinoY;

    while (MainWorld.Status(destinoX, destinoY) == _OBSTACULO) {
      std::cout << "Esa casilla se encuentra bloqueada por un obstaculo, elija otra" << std::endl;
      std::cout << "Posicion destino X: ";
      std::cin >> destinoX;
      std::cout << "Posicion del destino Y: ";
      std::cin >> destinoY;
    }

    Taxi MainTaxi(MainWorld, taxiX, taxiY, destinoX, destinoY);
  }
  else {

    std::ifstream Archivo;
    Archivo.open(argv[1]);
  
    if(Archivo.fail()) {
      std::cout << "Error al abrir el archivo" << argv[1] << std::endl;
      return -1;
    }

    Mundo MainWorld(Archivo);
    MainWorld.PrintMundo();

    Archivo.close();
  }

  return 0;
}