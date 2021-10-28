#include "../hpp/taxi.hpp"

Taxi::Taxi(Mundo mainWorld, int coordX, int coordY, int destX, int destY){      // Constructor por defecto
  world = mainWorld;
  taxiX = coordX;
  taxiY = coordY;
  destinoX = destX;
  destinoY = destY;
}

Taxi::~Taxi(){                                                                  // Destructor
}

void Taxi::PrintMundo() {                                                       // Representa el mundo por consola con el taxi en él
  std::vector<std::vector<int>> malla;
  malla = world.GetRejilla();
  malla[taxiX][taxiY] = taxi_;
  for(int i = 0; i < malla.size(); i++) {
    for (int j = 0; j < malla[0].size(); j++){
      std::cout << malla[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool Taxi::MovLegal(int movX, int movY) {                                       // Devuelve true o false si la casilla especificada existe y está vacía
  if(movX >= world.GetDimensionX() || movY >= world.GetDimensionY() || movX < 0 || movY < 0){
    return false;
  }
  if (world.Status(movX, movY) == obstaculo_) {
    return false;
  }
  return true;
}

bool Taxi::MovDer(std::vector<int> coord) {                                     // Devuelve true o false si un mov. hacia la derecha desde la casilla
  int nextpos = coord[1];                                                       // especificada es legal o no
  nextpos++;                                     
  if(MovLegal(coord[0], nextpos))
    return true;
  return false;
}

bool Taxi::MovIzq(std::vector<int> coord) {                                     // Devuelve true o false si un mov. hacia la izquierda desde la casilla
  int nextpos = coord[1];                                                       // especificada es legal o no
  nextpos--;
  if(MovLegal(coord[0], nextpos))
    return true;
  return false;
}

bool Taxi::MovArriba(std::vector<int> coord) {                                  // Devuelve true o false si un mov. hacia arriba desde la casilla
  int nextpos = coord[0];                                                       // especificada es legal o no
  nextpos--;
  if(MovLegal(nextpos, coord[1]))
    return true;
  return false;
}

bool Taxi::MovAbajo(std::vector<int> coord) {                                   // Devuelve true o false si un mov. hacia abajo desde la casilla
  int nextpos = coord[0];                                                       // especificada es legal o no
  nextpos++;
  if(MovLegal(nextpos, coord[1]))
    return true;
  return false;
}

/*std::vector<std::vector<int>> Taxi::CaminoMinimo(bool distancia) {                            // Calcula el camino mínimo dado el lugar de inicio del taxi y el destino
  std::vector<std::vector<int>> posibles;                                       // Posibles guarda las casillas alcanzadas a analizar
  std::vector<std::vector<std::vector<int>>> predecesores;                      // Predecesores guarda las casillas ya analizadas con su predecesor

  predecesores.resize(world.GetDimensionX());               
  for (int i = 0; i < world.GetDimensionX(); i++) {
    predecesores[i].resize(world.GetDimensionY());
  }

  std::vector<int> coordenadas(2);
  coordenadas[0] = taxiX;
  coordenadas[1] = taxiY;
  std::vector<int> auxiliar;
  posibles.push_back(coordenadas);                                              // Empezamos analizando la casilla donde se encuentra el taxi

  predecesores[taxiX][taxiY] = coordenadas;                                     // Su predecesor es ella misma

  while (coordenadas[0] != destinoX || coordenadas[1] != destinoY) {            // Mientras la casilla a analizar no sea el destino...

    posibles.pop_back();                                                        // Quitamos la casilla de posibles ya que la estamos analizando
    
    if (MovArriba(coordenadas)) {                                               // Si el taxi puede moverse hacia arriba/derecha/izquierda/abajo...
      auxiliar = coordenadas;                                                   // Guardamos en la casilla de encima/derecha/izquierda/abajo que su
      auxiliar[0]--;                                                            // predecesor es la que estamos analizando y la metemos en posibles
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.insert(posibles.begin(), auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }
    if (MovDer(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[1]++;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.insert(posibles.begin(), auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }
    if (MovAbajo(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[0]++;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.insert(posibles.begin(), auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }
    if (MovIzq(coordenadas)) {
      auxiliar = coordenadas;
      auxiliar[1]--;
      if (predecesores[auxiliar[0]][auxiliar[1]].size() == 0) {
        posibles.insert(posibles.begin(), auxiliar);
        predecesores[auxiliar[0]][auxiliar[1]] = coordenadas;
      }
    }

    if (posibles.empty()) {                                                       // Si no hay mas casillas a analizar (posibles está vacío))...
      std::vector<std::vector<int>> error;                                        // Devolvemos un camino vacío para indicar que no se puede llegar
      return error;
    }

    coordenadas[0] = posibles[posibles.size() - 1][0];                            // Establecemos como siguiente casilla a analizar la primera de posibles
    coordenadas[1] = posibles[posibles.size() - 1][1];
  }

  std::vector<std::vector<int>> caminoMinimo;
  caminoMinimo.push_back(coordenadas);                                            // Creamos el vector con el camino mínimo empezando por el destino

  do {                                                                            // Metemos por orden los predecesores de cada casilla en orden inverso
    caminoMinimo.push_back(predecesores[coordenadas[0]][coordenadas[1]]);         // dentro del vector hasta llegar a la casilla de inicio del taxi
    coordenadas[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    coordenadas[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (coordenadas[0] != taxiX || coordenadas[1] != taxiY);
  
  return caminoMinimo;
}*/

int* Taxi::Representacion(Mundo matriz, int level[]) {
                                          
  int contador = 0;

  for (int i = 0; i < matriz.GetDimensionX(); i++) {                             // Pasamos la matriz a el array de enteros "level" donde las casillas de
    for (int j = 0; j < matriz.GetDimensionY(); j++) {                           // carretera (0) se mantienen como 0 pero las casillas de obstáculos (1)
      if (matriz.GetRejilla()[i][j] == obstaculo_) {                             // se mantienen como 1, 2 o 3 siendo éstos unos índices que se usarán
        level[contador] = (rand() % 3) + 1;                                       // posteriormente para elegir una textura de obstáculo a representar
      }                                                                 
      else {                                                            
        level[contador] = vacio_;                                       
      }
      contador++;
    }
  }
  return level;
}

int* Taxi::Representacion(std::vector<std::vector<int>> camino, int dimensionX, int dimensionY, int levelPath[]) {
  
  for (int i = 0; i < camino.size(); i++) {                                       // Pasamos el vector con el camino mínimo calculado y lo pasamos a un
    levelPath[(camino[i][0]*dimensionY) + camino[i][1]] = 1;                      // array de enteros donde las casillas que no son parte del camino
  }                                                                               // valen 0 y las que si son parte del camino valen 1
  return levelPath;
}

std::vector<std::vector<std::vector<int>>> Taxi::Representacion(Mundo matriz) {

  std::vector<std::vector<std::vector<int>>> levelBordes(8);
  for (int i = 0; i < 8; i++) {                                                   // Recibimos 8 matrices que usaremos para 8 sprites distintos ya que en cada
    levelBordes[i].resize(matriz.GetDimensionX());                                // casilla pueden dibujarse hasta un máximo de dichos 8 sprites
    for (int j = 0; j < matriz.GetDimensionX(); j++) {
      levelBordes[i][j].resize(matriz.GetDimensionY());
      for (int k = 0; k < matriz.GetDimensionY(); k++) {
        levelBordes[i][j][k] = 0;
      }
    }
  }
  std::vector<int> coord(2, 0);

  for (coord[0] = 0; coord[0] < matriz.GetDimensionX(); coord[0]++) {
    for (coord[1] = 0; coord[1] < matriz.GetDimensionY(); coord[1]++) {           // Dada la posición de cada casilla se establecerá en cada mapa el número
      if (!matriz.Status(coord[0], coord[1])) {                                   // de sprite correspondiente y devolvemos el array de matrices
        if (matriz.Status(coord[0] + 1, coord[1]))
          levelBordes[0][coord[0]][coord[1]] = 1;
        if (matriz.Status(coord[0] - 1, coord[1]))
          levelBordes[1][coord[0]][coord[1]] = 2;
        if (matriz.Status(coord[0], coord[1] + 1))
          levelBordes[2][coord[0]][coord[1]] = 3;
        if (matriz.Status(coord[0], coord[1] - 1))
          levelBordes[3][coord[0]][coord[1]] = 4;
        if (matriz.Status(coord[0], coord[1] - 1) && matriz.Status(coord[0] + 1, coord[1]))
          levelBordes[4][coord[0]][coord[1]] = 5;
        if (matriz.Status(coord[0], coord[1] - 1) && matriz.Status(coord[0] - 1, coord[1]))
          levelBordes[5][coord[0]][coord[1]] = 6;
        if (matriz.Status(coord[0], coord[1] + 1) && matriz.Status(coord[0] - 1, coord[1]))
          levelBordes[6][coord[0]][coord[1]] = 7;
        if (matriz.Status(coord[0], coord[1] + 1) && matriz.Status(coord[0] + 1, coord[1]))
          levelBordes[7][coord[0]][coord[1]] = 8;
      }
      else if (matriz.Status(coord[0], coord[1])) {
        if (!matriz.Status(coord[0], coord[1] - 1) && !matriz.Status(coord[0] + 1, coord[1]) && !matriz.Status(coord[0] + 1, coord[1] - 1))
          levelBordes[6][coord[0] + 1][coord[1] - 1] = 7;
        if (!matriz.Status(coord[0], coord[1] - 1) && !matriz.Status(coord[0] - 1, coord[1]) && !matriz.Status(coord[0] - 1, coord[1] - 1))
          levelBordes[7][coord[0] - 1][coord[1] - 1] = 8;
        if (!matriz.Status(coord[0], coord[1] + 1) && !matriz.Status(coord[0] - 1, coord[1]) && !matriz.Status(coord[0] - 1, coord[1] + 1))
          levelBordes[4][coord[0] - 1][coord[1] + 1] = 5;
        if (!matriz.Status(coord[0], coord[1] + 1) && !matriz.Status(coord[0] + 1, coord[1]) && !matriz.Status(coord[0] + 1, coord[1] + 1))
          levelBordes[5][coord[0] + 1][coord[1] + 1] = 6;
      }
    }
  }
  return levelBordes;
}

std::vector<std::vector<int>> Taxi::CaminoMinimo(bool distancia) {

  std::vector<std::vector<Nodo>> matrizNodos;
  std::vector<std::vector<int>> abierta;
  std::vector<std::vector<int>> cerrada;

  std::vector<int> nodoActual {taxiX, taxiY};

  Nodo nodoStart(0, 0, taxiX, taxiY);

  nodoStart.set_h(Heuristica(distancia, taxiX, taxiY));

  matrizNodos.resize(world.GetDimensionX());
  for (int i = 0; i < matrizNodos.size(); i++) {
    matrizNodos[i].resize(world.GetDimensionY());
  }
  
  matrizNodos[taxiX][taxiY] = nodoStart;

  abierta.push_back(nodoActual);

  while ((nodoActual[0] != destinoX || nodoActual[1] != destinoY) && !abierta.empty()) {

    float f = INFINITY;
    std::vector<int> nodoSiguiente(2);
    for (int i = 0; i < abierta.size(); i++) {
      if ((matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[nodoActual[0]][nodoActual[1]].get_g() + 10) < f) {
        f = (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[nodoActual[0]][nodoActual[1]].get_g() + 10);
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }
    }
    for (int i = 0; i < abierta.size(); i++) {
      if (abierta[i][0] == nodoSiguiente[0] && abierta[i][1] == nodoSiguiente[1]) {
        abierta.erase(abierta.begin() + i);
      }
    }
    cerrada.push_back(nodoSiguiente);
    nodoActual = nodoSiguiente;

    if (MovArriba(nodoActual)) {
      bool pertenece = 0;
      for (int i = 0; i < cerrada.size(); i++) {
        if ((nodoActual[0] - 1 == cerrada[i][0]) && (nodoActual[1] == cerrada[i][1])) {
          pertenece = 1;
        }
      }
      if (pertenece == 0) {
        for (int i = 0; i < abierta.size(); i++) {
          if (nodoActual[0] - 1 == abierta[i][0] && nodoActual[1] == abierta[i][1]) {
            pertenece = 1;
          }
        }
        if (pertenece) {
          if (matrizNodos[nodoActual[0] - 1][nodoActual[1]].get_g() > 10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
            matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_h(Heuristica(distancia, nodoActual[0] - 1, nodoActual[1]));
            matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
            matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_padre(nodoActual[0], nodoActual[1]);
          }
        }
        else {
          matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_h(Heuristica(distancia, nodoActual[0] - 1, nodoActual[1]));
          matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
          matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_padre(nodoActual[0], nodoActual[1]);
          std::vector<int> aux {nodoActual[0] - 1, nodoActual[1]};
          abierta.push_back(aux);
        }
      }
    }
    else {
      if (nodoActual[0] - 1 >= world.GetDimensionX() || nodoActual[1] >= world.GetDimensionY() || nodoActual[0] - 1 < 0 || nodoActual[1] < 0) {
      }
      else {
        matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_obstaculo();
      }
    }
    if (MovDer(nodoActual)) {
      bool pertenece = 0;
      for (int i = 0; i < cerrada.size(); i++) {
        if ((nodoActual[0] == cerrada[i][0]) && (nodoActual[1] + 1 == cerrada[i][1])) {
            pertenece = 1;
        }
      }
      if (pertenece == 0) {
        for (int i = 0; i < abierta.size(); i++) {
          if (nodoActual[0] == abierta[i][0] && nodoActual[1] + 1 == abierta[i][1]) {
            pertenece = 1;
          }
        }
        if (pertenece) {
          if (matrizNodos[nodoActual[0]][nodoActual[1] + 1].get_g() > 10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
            matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_h(Heuristica(distancia, nodoActual[0], nodoActual[1] + 1));
            matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
            matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_padre(nodoActual[0], nodoActual[1]);
          }
        }
        else {
          matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_h(Heuristica(distancia, nodoActual[0], nodoActual[1] + 1));
          matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
          matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_padre(nodoActual[0], nodoActual[1]);
          std::vector<int> aux {nodoActual[0], nodoActual[1] + 1};
          abierta.push_back(aux);
        }
      }
    }
    else {
      if (nodoActual[0] >= world.GetDimensionX() || nodoActual[1] + 1 >= world.GetDimensionY() || nodoActual[0] < 0 || nodoActual[1] + 1 < 0) {
      }
      else {
        matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_obstaculo();
      }
    }
    if (MovAbajo(nodoActual)) {
      bool pertenece = 0;
      for (int i = 0; i < cerrada.size(); i++) {
        if ((nodoActual[0] + 1 == cerrada[i][0]) && (nodoActual[1] == cerrada[i][1])) {
          pertenece = 1;
        }
      }
      if (pertenece == 0) {
        for (int i = 0; i < abierta.size(); i++) {
          if (nodoActual[0] + 1 == abierta[i][0] && nodoActual[1] == abierta[i][1]) {
            pertenece = 1;
          }
        }
        if (pertenece) {
          if (matrizNodos[nodoActual[0] + 1][nodoActual[1]].get_g() > 10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
            matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_h(Heuristica(distancia, nodoActual[0] + 1, nodoActual[1]));
            matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
            matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_padre(nodoActual[0], nodoActual[1]);
          }
        }
        else {
          matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_h(Heuristica(distancia, nodoActual[0] + 1, nodoActual[1]));
          matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
          matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_padre(nodoActual[0], nodoActual[1]);
          std::vector<int> aux {nodoActual[0] + 1, nodoActual[1]};
          abierta.push_back(aux);
        }
      }
    }
    else {
      if (nodoActual[0] + 1 >= world.GetDimensionX() || nodoActual[1] >= world.GetDimensionY() || nodoActual[0] + 1 < 0 || nodoActual[1] < 0) {
      }
      else {
        matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_obstaculo();
      }
    }
    if (MovIzq(nodoActual)) {
      bool pertenece = 0;
      for (int i = 0; i < cerrada.size(); i++) {
        if (!(nodoActual[0] == cerrada[i][0]) && !(nodoActual[1] - 1 == cerrada[i][1])) {
          pertenece = 1;
        }
      }
      if (pertenece = 0) {
        for (int i = 0; i < abierta.size(); i++) {
          if (nodoActual[0] == abierta[i][0] && nodoActual[1] - 1 == abierta[i][1]) {
            pertenece = 1;
          }
        }
        if (pertenece) {
          if (matrizNodos[nodoActual[0]][nodoActual[1] - 1].get_g() > 10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
            matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_h(Heuristica(distancia, nodoActual[0], nodoActual[1] - 1));
            matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
            matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_padre(nodoActual[0], nodoActual[1]);
          }
        }
        else {
          matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_h(Heuristica(distancia, nodoActual[0], nodoActual[1] - 1));
          matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_coste(10 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
          matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_padre(nodoActual[0], nodoActual[1]);
          std::vector<int> aux {nodoActual[0], nodoActual[1] - 1};
          abierta.push_back(aux);
        }
      }
    }
    else {
      if (nodoActual[0] >= world.GetDimensionX() || nodoActual[1] - 1 >= world.GetDimensionY() || nodoActual[0] < 0 || nodoActual[1] - 1 < 0) {
      }
      else {
        matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_obstaculo();
      }
    }
  }

  std::vector<std::vector<int>> caminoMinimo;
  if (nodoActual[0] != destinoX && nodoActual[1] != destinoY) {
    return caminoMinimo;
  }
  caminoMinimo.push_back(nodoActual);                                                      // Creamos el vector con el camino mínimo empezando por el destino

  do {                                                                                     // Metemos por orden los predecesores de cada casilla en orden inverso
    caminoMinimo.push_back(matrizNodos[nodoActual[0]][nodoActual[1]].get_padre());         // dentro del vector hasta llegar a la casilla de inicio del taxi
    nodoActual[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    nodoActual[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (nodoActual[0] != taxiX || nodoActual[1] != taxiY);
  
  return caminoMinimo;
}

float Taxi::Heuristica(bool distancia, int coordx, int coordy) {

  if (distancia == 0) {
    float manhattan = (abs(coordx - destinoX)) + (abs(coordy - destinoY));
    return manhattan;
  }
  else {
    float euclidea = sqrt(pow((coordx - destinoX), 2) + pow((coordy - destinoY), 2));
    return euclidea;
  }
}