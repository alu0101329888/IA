#ifndef TAXI_H
#define TAXI_H

#include "nodo.hpp"
#include "mundo.hpp"

class Taxi {
  private:
  
    int taxiX, taxiY;
    int destinoX, destinoY;
    Mundo world;
    
  public:

    Taxi(Mundo mainWorld, int coordX, int coordY, int destX, int destY);
    ~Taxi();

    bool MovDer(std::vector<int>);
    bool MovIzq(std::vector<int>);
    bool MovArriba(std::vector<int>);
    bool MovAbajo(std::vector<int>);
    bool MovArribaDer(std::vector<int>);
    bool MovArribaIzq(std::vector<int>);
    bool MovAbajoDer(std::vector<int>);
    bool MovAbajoIzq(std::vector<int>);

    float Heuristica(bool distancia, int coordX, int coordY);

    bool MovLegal(int movX, int movY);

    void PrintMundo(void);

    std::vector<std::vector<int>> CaminoMinimo4(bool distancia);
    std::vector<std::vector<int>> CaminoMinimo8(bool distancia);

    int* Representacion(Mundo matriz, int level[]);
    int* Representacion(std::vector<std::vector<int>> camino, int dimensionX, int dimensionY, int levelPath[]);
    std::vector<std::vector<std::vector<int>>>  Representacion(Mundo matriz);
};

#endif
