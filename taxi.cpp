#include "taxi.hpp"

Taxi::Taxi(Mundo MainWorld, int coordX, int coordY, int destX, int destY){
  World = MainWorld;
  taxiX = coordX;
  taxiY = coordY;
  destinoX = destX;
  destinoY = destY;
}

Taxi::~Taxi(){}

std::vector<int> Taxi::GetTaxiPos(void){
  std::vector<int> pos_taxi;
  pos_taxi.push_back(taxiX);
  pos_taxi.push_back(taxiY);
  return pos_taxi;
}

void Taxi::SetTaxiPos(int X, int Y){
  
}

bool Taxi::MovLegal(int movX, int movY) {
  if(movX >= World.GetDimensionX() || movY >= World.GetDimensionY()){
    return false;
  }
  if (World.Status(movX, movY) == _OBSTACULO) {
    return false;
  }
  return true;
}