#include "mundo.hpp"

Mundo::Mundo(){
}

void Mundo::Resize(int DimX, int DimY) {
  Rejilla.resize(DimX);
  for (int i = 0; i < DimX; i++) {
    Rejilla[i].resize(DimY);
  }
  DimensionX = DimX;
  DimensionY = DimY;
}

void Mundo::Load(std::ifstream &Fichero) {
  std::string Lectura;
  int Columna = 0;
  while (!Fichero.eof()) {
    Rejilla.resize(Rejilla.size() + 1);
    std::getline(Fichero, Lectura);
    for (int Fila = 0; Fila < Lectura.size(); Fila++) {
      Rejilla[Columna].push_back((int)Lectura[Fila] - 48);
    }
    Columna++;
  }
  DimensionX = Rejilla.size();
  DimensionY = Rejilla[0].size();
}

int Mundo:: GetDimensionX(void) {
  return DimensionX;
}
int Mundo:: GetDimensionY(void) {
  return DimensionY;
}

std::vector<std::vector<int>> Mundo::GetRejilla() {
  return Rejilla;
}

void Mundo::PrintMundo() {
  for(int i = 0; i < Rejilla.size(); i++) {
    for (int j = 0; j < Rejilla[i].size(); j++){
      std::cout << Rejilla[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Mundo::Random(int Obstaculos) {
  int randX, randY;
  while (Obstaculos != 0) {
    randX = rand() % DimensionX + 0;
    randY = rand() % DimensionY + 0;
    if (Rejilla[randX][randY] != obstaculo_) {
      Rejilla[randX][randY] = obstaculo_;
      Obstaculos--;
    }
  }
  return 0;
}

int Mundo::Status(int X, int Y) {
  return Rejilla[X][Y];
}