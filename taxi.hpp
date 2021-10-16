#ifndef TAXI_H
#define TAXI_H

#include "mundo.hpp"

class Taxi {
  private:
    int taxiX, taxiY;
    int destinoX, destinoY;
    Mundo World;

  public:
    Taxi(Mundo MainWorld, int coordX, int coordY, int destX, int destY);
    ~Taxi();
    std::vector<int> GetTaxiPos(void);
    void SetTaxiPos(int X, int Y);
    void SetDestino(int  X, int Y);
    bool MovDer(std::vector<int>);
    bool MovIzq(std::vector<int>);
    bool MovArriba(std::vector<int>);
    bool MovAbajo(std::vector<int>);
    bool MovLegal(int movX, int movY);
    void PrintMundo(void);
    std::vector<std::vector<int>> CaminoMinimo();
    //PrinTaxiEnv()
};

#endif