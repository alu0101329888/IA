#ifndef MUNDO_H
#define MUNDO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define _OBSTACULO 1
#define _VACIO 0

class Mundo {
  private:
    std::vector<std::vector<int>> Rejilla;
    int DimensionX, DimensionY;
  public:
    Mundo();
    Mundo(int DimX, int DimY);
    Mundo(std::ifstream &Fichero);
    int Random(int Obstaculos);
    void PrintMundo();
    int Status(int, int);
    int GetDimensionX();
    int GetDimensionY();
};

#endif

/*Constructor destructor

Matriz

Resize

Cambiar estado de casilla

Devolver estado de casilla


Siguiente casilla*/

