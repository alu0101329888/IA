#include "taxi.hpp"

Taxi::Taxi(Mundo MainWorld, int coordX, int coordY, int destX, int destY){
  World = MainWorld;
  taxiX = coordX;
  taxiY = coordY;
  destinoX = destX;
  destinoY = destY;
}

Taxi::~Taxi(){}

std::vector<int> Taxi::GetTaxiPos(){
  std::vector<int> pos_taxi;
  pos_taxi.push_back(taxiX);
  pos_taxi.push_back(taxiY);
  return pos_taxi;
}

void Taxi::SetTaxiPos(int X, int Y){
  taxiX = X;
  taxiY = Y;
}

void Taxi::SetDestino(int X, int Y) {
  destinoX = X;
  destinoY = Y;
}

void Taxi::PrintMundo() {
  std::vector<std::vector<int>> malla;
  malla = World.GetRejilla();
  malla[taxiX][taxiY] = taxi_;
  for(int i = 0; i < malla.size(); i++) {
    for (int j = 0; j < malla[0].size(); j++){
      std::cout << malla[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

//Movimientos
bool Taxi::MovLegal(int movX, int movY) {
  if(movX >= World.GetDimensionX() || movY >= World.GetDimensionY() || movX < 0 || movY < 0){
    return false;
  }
  if (World.Status(movX, movY) == obstaculo_) {
    return false;
  }
  return true;
}

bool Taxi::MovDer(std::vector<int> coord) {
  int nextpos = coord[1];
  nextpos++;                                     
  if(MovLegal(coord[0], nextpos))
    return true;
  return false;
}

bool Taxi::MovIzq(std::vector<int> coord) {
  int nextpos = coord[1];
  nextpos--;
  if(MovLegal(coord[0], nextpos))
    return true;
  return false;
}

bool Taxi::MovArriba(std::vector<int> coord) {
  int nextpos = coord[0];
  nextpos--;
  if(MovLegal(nextpos, coord[1]))
    return true;
  return false;
}

bool Taxi::MovAbajo(std::vector<int> coord) {
  int nextpos = coord[0];
  nextpos++;
  if(MovLegal(nextpos, coord[1]))
    return true;
  return false;
}

std::vector<std::vector<int>> Taxi::CaminoMinimo() {
  std::vector<std::vector<int>> posibles;
  std::vector<std::vector<std::vector<int>>> predecesores;  //Vector que guarda las casillas visitadas 
                                                            //y los predecesores de cada una
  predecesores.resize(World.GetDimensionX());               
  for (int i = 0; i < World.GetDimensionX(); i++) {
    predecesores[i].resize(World.GetDimensionY());
  }

  std::vector<int> coordenadas(2);
  coordenadas[0] = taxiX;
  coordenadas[1] = taxiY;
  std::vector<int> auxiliar;
  posibles.push_back(coordenadas);

  predecesores[taxiX][taxiY] = coordenadas;

  while (coordenadas[0] != destinoX || coordenadas[1] != destinoY) { // Comprueba el ultimo elemento de posibles para ver si es el destino
    
    posibles.pop_back();
    
    if (MovArriba(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[0]--;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.push_back(auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }
    if (MovDer(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[1]++;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.push_back(auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }
    if (MovAbajo(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[0]++;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.push_back(auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }
    if (MovIzq(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[1]--;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.push_back(auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }

    coordenadas[0] = posibles[posibles.size() - 1][0];
    coordenadas[1] = posibles[posibles.size() - 1][1];

  }

  std::vector<std::vector<int>> caminoMinimo;
  caminoMinimo.push_back(coordenadas);

  do {
    caminoMinimo.push_back(predecesores[coordenadas[0]][coordenadas[1]]);
    coordenadas[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    coordenadas[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (coordenadas[0] != taxiX || coordenadas[1] != taxiY);
  
  return caminoMinimo;
}
