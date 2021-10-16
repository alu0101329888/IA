#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "mundo.hpp"
#include "taxi.hpp"

// g++ -g -Wall main.cpp mundo.cpp taxi.cpp -o main

int main(int argc, char *argv[]) {

  int dimX, dimY, taxiX, taxiY, destinoX, destinoY, numObstaculos;
  int opcion;
  Mundo MainWorld;
  
  //Menu
  if (argc != 2) {
    
    std::cout << "No se ha especificado un fichero del cual leer, por tanto se introduciran los obstaculos de manera aleatoria." << std::endl;
    std::cout << "Introduzca las dimensiones de la matriz X*Y" << std::endl;
    do {
      std::cout << "Dimension X: ";
      std::cin >> dimX;
      std::cout << "Dimension Y: ";
      std::cin >> dimY;
      if (dimX <= 0 || dimY <= 0) {
        std::cout << "El valor no puede ser menor o igual que cero" << std::endl;
      }
    } while (dimX <= 0 || dimY <= 0);

    MainWorld.Resize(dimX, dimY);
    
    std::cout << "Introduzca el numero de obstaculos a colocar o -1 para elegir uno aleatorio: ";
    std::cin >> opcion;

    while (opcion < -1 || opcion > (dimX*dimY - 2)) {
        std::cout << "Cantidad de obstaculos no permitida, escoja otra cantidad o seleccione -1 para poner un numero aleatorio" << std::endl;
        std::cin >> opcion;
    }

    if (opcion == -1) {
      numObstaculos = rand() % dimX*dimY + 0;
      std::cout << "Elegidos " << numObstaculos << " nº de obstaculos" << std::endl;
      MainWorld.Random(numObstaculos); //genera un numero aleatorio entre 0 y dimX*dimY
    }
    else {
      numObstaculos = opcion;
      std::cout << "Elegidos " << numObstaculos << " nº de obstaculos" << std::endl;
      MainWorld.Random(numObstaculos);
    }

    MainWorld.PrintMundo();

    do {
      std::cout << "Introduzca la coordenada en donde se situara el taxi" << std::endl << "Posicion del taxi X: ";
      std::cin >> taxiX;
      std::cout << "Posicion del taxi Y: ";
      std::cin >> taxiY;
      if (taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_)) {
        std::cout << "Esa casilla no existe o se encuentra obstaculizada" << std::endl;
      }
    } while(taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_));

    do {
      std::cout << "Introduzca la coordenada en donde se situara el destino" << std::endl << "Posicion del destino X: ";
      std::cin >> destinoX;
      std::cout << "Posicion del destino Y: ";
      std::cin >> destinoY;
      if (destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY) || (MainWorld.Status(destinoX, destinoY) == obstaculo_)) {
        std::cout << "Esa casilla no existe, se encuentra obstaculizada o es la de inicio" << std::endl;
      }
    } while(destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY) || (MainWorld.Status(destinoX, destinoY) == obstaculo_));
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
  
  for (int i = (Camino.size() - 1); i >= 0; i--) {
    std::cout << Camino[i][0] << " - " << Camino[i][1] << std::endl;
  }

  return 0;
}