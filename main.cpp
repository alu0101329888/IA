#include <SFML/Graphics.hpp>
#include "mapa.hpp"
#include "mundo.hpp"
#include "taxi.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// Para compilar se requieren la librerías de SFML -> sudo apt-get install libsfml-dev

// Use "make" para compilar y "make clean" para limpiar el directorio de archivos .o y el ejecutable

// Taxi es el ejecutable final, ejecute con ./Taxi ó ./Taxi <archivo.extension> para leer de un archivo

int main(int argc, char *argv[]) {

  int dimX, dimY, taxiX, taxiY, destinoX, destinoY, numObstaculos;      // Variables donde guardaremos las dimensiones de la matriz, posición del taxi,
  int opcion;                                                           // posición del destino, el número de obstáculos que tendrá nuestro mundo,
  Mundo MainWorld;                                                      // una variable opción para elegir a través del menú y nuestro mundo principal.
                                                                        
  if (argc != 2) {                                                      // En el caso en el que el programa se abra sin especificar un archivo con el mundo

    std::cout << "No se ha especificado un fichero del cual leer, por tanto se introduciran los obstaculos de manera aleatoria." << std::endl;
    std::cout << "Introduzca las dimensiones de la matriz X*Y" << std::endl;

    do {                                                                // Recogida del tamaño del mundo
      std::cout << "Dimension X: ";
      std::cin >> dimX;
      std::cout << "Dimension Y: ";
      std::cin >> dimY;
      if (dimX <= 0 || dimY <= 0) {
        std::cout << "El valor no puede ser menor o igual que cero" << std::endl;
      }
    } while (dimX <= 0 || dimY <= 0);

    MainWorld.Resize(dimX, dimY);                                       // Establecemos el tamaño del mundo
    
    std::cout << "Introduzca el numero de obstaculos a colocar o -1 para elegir uno aleatorio: ";
    std::cin >> opcion;

    while (opcion < -1 || opcion > (dimX*dimY - 2)) {                   // Elegimos el número de obstáculos que se colocarán aleatoriamente en el mundo
        std::cout << "Cantidad de obstaculos no permitida, escoja otra cantidad o seleccione -1 para poner un numero aleatorio" << std::endl;
        std::cin >> opcion;
    }

    if (opcion == -1) {                                                 // Genera un numero aleatorio entre 0 y dimX*dimY
      numObstaculos = (rand() % dimX*dimY + 0) - 2;                     // (-2 para que haya espacio para el taxi y el destino, una casilla cada una)
      std::cout << "Elegidos " << numObstaculos << " nº de obstaculos" << std::endl;
      MainWorld.Random(numObstaculos);                                  // Se colocan numObstaculos obstáculos de manera aleatoria en el mundo                    
    }
    else {                                                              // Se usa el número de obstáculos elegido por el usuario
      numObstaculos = opcion;
      std::cout << "Elegidos " << numObstaculos << " nº de obstaculos" << std::endl;
      MainWorld.Random(numObstaculos);                                  // Se colocan numObstaculos obstáculos de manera aleatoria en el mundo
    }

  }
  else {                                                                // En el caso en el que se especifique un archivo del cual leer al ejecutar
    std::ifstream Archivo;                                              // el programa, se lee dicho archivo y se crea un mundo con él
    Archivo.open(argv[1]);
                                                                        // El archivo debe contener una matriz de ceros y unos del estilo:
    if(Archivo.fail()) {                                                // 001101100101010
      std::cout << "Error al abrir el archivo" << argv[1] << std::endl; // 111011001001001            Donde: 0 = carretera / vacío
      return -1;                                                        // 000100001000000                   1 = obstáculo
    }                                                                   //       ...

    MainWorld.Load(Archivo);                                            // Se carga el archivo en el mundo
    dimX = MainWorld.GetDimensionX();                                   // Pasamos a las variables de la dimensión del mundo, el tamaño de la matriz
    dimY = MainWorld.GetDimensionY();
 
    Archivo.close();
  }

  MainWorld.PrintMundo();

  do {                                                                  // Recogemos la posición del taxi en el mundo
    std::cout << "Introduzca la coordenada en donde se situara el taxi" << std::endl << "Posicion del taxi X: ";
    std::cin >> taxiX;
    std::cout << "Posicion del taxi Y: ";
    std::cin >> taxiY;
    if (taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_)) {
      std::cout << "Esa casilla no existe o se encuentra obstaculizada" << std::endl;
    }
  } while(taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_));

  do {                                                                  // Recogemos la posición del destino en el mundo
    std::cout << "Introduzca la coordenada en donde se situara el destino" << std::endl << "Posicion del destino X: ";
    std::cin >> destinoX;
    std::cout << "Posicion del destino Y: ";
    std::cin >> destinoY;
    if (destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY) || (MainWorld.Status(destinoX, destinoY) == obstaculo_)) {
      std::cout << "Esa casilla no existe, se encuentra obstaculizada o es la de inicio" << std::endl;
    }
  } while(destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY) || (MainWorld.Status(destinoX, destinoY) == obstaculo_));
  
  Taxi MainTaxi(MainWorld, taxiX, taxiY, destinoX, destinoY);           // Creamos la clase Taxi con el mundo y las coordenadas especificadas

  std::vector<std::vector<int>> Camino = MainTaxi.CaminoMinimo();       // Calculamos el camino mínimo entre las coordenadas de inicio y destino
  if (Camino.size() == 0) {                                             
    std::cout << "El taxi no puede llegar a su destino" << std::endl;   // Si el camino nos llega vacío significa que no hay manera de que el taxi
    return -1;                                                          // llegue al destino de ninguna forma
  }

  sf::RenderWindow window(sf::VideoMode(dimY*32, dimX*32), "Mapa");     // Abrimos una ventana nueva

  int level[dimX*dimY] = {0}; 
  int levelPath[dimX*dimY] = {0};
  MainTaxi.Representacion(MainWorld, level);                            // Obtenemos un array de enteros con el mundo para representarlo en ventana
  MainTaxi.Representacion(Camino, dimX, dimY, levelPath);               // Obtenemos un array de enteros con el camino para representarlo en ventana

  Mapa background;                                                      // Creamos y cargamos un mapa con el mundo
  if (!background.load("casillas.png", sf::Vector2u(32, 32), level, dimY, dimX)) {
    return -1;
  }

  Mapa path;                                                            // Creamos y cargamos un mapa con el camino
  if (!path.load("camino.png", sf::Vector2u(32, 32), levelPath, dimY, dimX)) {
    return -1;
  }

  while (window.isOpen()) {                                             // Mientras la ventana esté abierta...

    sf::Event event;                                                    // Creamos un evento que manejar
    while (window.pollEvent(event)) {                                   // Si se ha recogido un evento...
      if(event.type == sf::Event::Closed) {                             // Si el evento es el de cerrar la ventana, la cerramos
        window.close();
      }
    }

    window.clear();                                                     // Limpiamos lo dibujado en ventana
    window.draw(background);                                            // Dibujamos el fondo en ventana
    window.draw(path);                                                  // Dibujamos (encima del fondo) el camino en la ventana
    window.display();                                                   // Representamos en pantalla lo dibujado
  }
  return 0;
}                                                                       // FIN
