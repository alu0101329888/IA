#include "mundo.hpp"

Mundo::Mundo(){
}

Mundo::Mundo(int DimX, int DimY) {
  Rejilla.resize(DimY);
  for (int i = 0; i < DimY; i++) {
    Rejilla[i].resize(DimX);
  }
  DimensionX = DimX;
  DimensionY = DimY;
}

Mundo::Mundo(std::ifstream & Fichero) {
  std::string Lectura;
  int Columna = 0;
  while (!Fichero.eof()) {
    Rejilla.resize(Rejilla.size() + 1);
    std::getline(Fichero, Lectura);
    for (int Fila = 0; Fila < Lectura.size(); Fila++) {
      Rejilla[Columna].push_back((int)Lectura[Fila] - '0');
    }
    Columna++;
  }
  DimensionX = Rejilla[0].size();
  DimensionY = Rejilla.size();
}

int Mundo:: GetDimensionX(void) {
  return DimensionX;
}
int Mundo:: GetDimensionY(void) {
  return DimensionY;
}

void Mundo::PrintMundo() {
  for(int i = 0; i < Rejilla.size(); i++) {
    for (int j = 0; j < Rejilla[i].size(); j ++){
      std::cout << Rejilla[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Mundo::Random(int Obstaculos) {
  int randX, randY;
  if (Obstaculos > ((Rejilla.size() * Rejilla[0].size()) - 2)) {
    return -1;
  }
  while (Obstaculos != 0) {
    randX = rand() % DimensionX + 0;
    randY = rand() % DimensionY + 0;
    if (Rejilla[randY][randX] != _OBSTACULO) {
      Rejilla[randY][randX] = _OBSTACULO;
      Obstaculos--;
    }
  }
  return 0;
}

int Mundo::Status(int X, int Y) {
  return Rejilla[Y][X];
}