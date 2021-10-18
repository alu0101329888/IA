#ifndef TAXI_H
#define TAXI_H

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

    bool MovLegal(int movX, int movY);

    void PrintMundo(void);

    std::vector<std::vector<int>> CaminoMinimo();

    int* Representacion(Mundo matriz, int level[]);
    int* Representacion(std::vector<std::vector<int>> camino, int dimensionX, int dimensionY, int levelPath[]);
    std::vector<std::vector<std::vector<int>>>  Representacion(Mundo matriz);
};

#endif
