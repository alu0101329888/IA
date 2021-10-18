#include "../hpp/mundo.hpp"

Mundo::Mundo(){                                                                 // Constructor por defecto
}

void Mundo::Resize(int DimX, int DimY) {                                        // Establece el tamaño de la matriz del mundo a lo dado
  rejilla.resize(DimX);                                                         // y guarda las dimensiones en las variables privadas
  for (int i = 0; i < DimX; i++) {
    rejilla[i].resize(DimY);
  }
  dimensionX = DimX;
  dimensionY = DimY;
}

void Mundo::Load(std::ifstream &Fichero) {                                      // Lee desde un fichero una matriz de mundo y la guarda
  std::string Lectura;                                                          
  int Columna = 0;                                                              // Véase main-sfml.cpp para una explicación del formato del fichero
  while (!Fichero.eof()) {
    rejilla.resize(rejilla.size() + 1);
    std::getline(Fichero, Lectura);
    for (int Fila = 0; Fila < Lectura.size(); Fila++) {
      rejilla[Columna].push_back((int)Lectura[Fila] - 48);
    }
    Columna++;
  }
  dimensionX = rejilla.size();
  dimensionY = rejilla[0].size();
}

int Mundo::GetDimensionX(void) {                                                // Devuelve la dimensión x de la matriz
  return dimensionX;
}
int Mundo::GetDimensionY(void) {                                                // Devuelve la dimensión y de la matriz
  return dimensionY;
}

std::vector<std::vector<int>> Mundo::GetRejilla() {                             // Devuelve la matriz
  return rejilla;
}

void Mundo::PrintMundo() {                                                      // Representa el mundo por consola
  for(int i = 0; i < rejilla.size(); i++) {
    for (int j = 0; j < rejilla[i].size(); j++){
      std::cout << rejilla[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Mundo::Random(int Obstaculos) {                                             // Coloca un número "Obstaculos" de obstáculos de manera aleatoria
  int randX, randY;                                                             // en las casillas de la matriz
  while (Obstaculos != 0) {
    randX = rand() % dimensionX + 0;
    randY = rand() % dimensionY + 0;
    if (rejilla[randX][randY] != obstaculo_) {
      rejilla[randX][randY] = obstaculo_;
      Obstaculos--;
    }
  }
  return 0;
}

int Mundo::Status(int X, int Y) {                                               // Devuelve el valor de una casilla dada 
  if (X < dimensionX && X >= 0 && Y < dimensionY && Y >= 0)
    return rejilla[X][Y];
  else
    return -1;
}
