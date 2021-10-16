#ifndef MUNDO_H
#define MUNDO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define taxi_ 4
#define obstaculo_ 1
#define vacio_ 0

class Mundo {
  private:
    std::vector<std::vector<int>> Rejilla;
    int DimensionX, DimensionY; 
  public:
    Mundo();
    void Resize(int DimX, int DimY);
    void Load(std::ifstream &Fichero);
    int Random(int Obstaculos);
    void PrintMundo();
    int Status(int, int);
    int GetDimensionX();
    int GetDimensionY();
    std::vector<std::vector<int>> GetRejilla();
};

#endif

/*Constructor destructor

Matriz

Resize

Cambiar estado de casilla

Devolver estado de casilla


Siguiente casilla*/

