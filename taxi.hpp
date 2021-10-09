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
    bool MovLegal(int movX, int movY);
    //PrinTaxiEnv()
};

#endif