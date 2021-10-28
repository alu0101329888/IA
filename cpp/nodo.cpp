#include "../hpp/nodo.hpp"
Nodo::Nodo() {
}

Nodo::Nodo(bool obst, float g, int padrex, int padrey) {
  if (obst == true) {
    obstaculo = true;
  }
  else {
    coste = g;
    padrex_ = padrex;
    padrey_ = padrey;
  }
}

Nodo::~Nodo() {
}

void Nodo::set_coste(float g) {
  coste = g;
}

void Nodo::set_padre(int padrex, int padrey) {
  padrex_ = padrex;
  padrey_ = padrey;
}

float Nodo::get_g(){
  return coste;
}

float Nodo::get_h() {
  return h;
}   

bool Nodo::get_obstaculo() {
  return obstaculo;
}

std::vector<int> Nodo::get_padre() {
  std::vector<int> coord {padrex_, padrey_};
  return coord;
}

void Nodo::set_h(float distancia) {
  h = distancia;
}

void Nodo::set_obstaculo() {
  obstaculo = 1;
}