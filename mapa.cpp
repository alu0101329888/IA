#include "mapa.hpp"
                                                                                        // Cargamos un mapa para representar por ventana
bool Mapa::load(const std::string& tileset, sf::Vector2u tileSize, int* tiles, unsigned int ancho, unsigned int alto) {

  if (!m_tileset.loadFromFile(tileset)) {                                               // Carga la textura y devuelve false si falla en m_tileset
    return false;
  }
        
  m_vertices.setPrimitiveType(sf::Quads);                                               // Establece la representación como quad para tener 4 vértices
  m_vertices.resize(ancho * alto * 4);                                                  // Establece el tamaño del quad como ancho*alto*4 (pixeles)

  for (unsigned int i = 0; i < ancho; ++i) {                                            // Para cada casilla...
    for (unsigned int j = 0; j < alto; ++j) {                                          
      int tileNumber = tiles[i + j * ancho];                                            // Cogemos el valor de la casilla

      int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);                       // Determina la posición (en píxeles) del sprite según el
      int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);                       // valor de la casilla

      sf::Vertex* quad = &m_vertices[(i + j * ancho) * 4];                              // Obtiene un puntero al quad de la casilla a representar

      quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);                  // Definimos los 4 vértices del quad a representar por la
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);            // casilla en la ventana
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);               // Definimos los 4 vértices del sprite a representar por la
      quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);         // casilla en el archivo con los sprites
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
  }
  return true;                                                                          // Devuelve true al terminar
}


void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  states.transform *= getTransform();                                                   // Aplicamos el transform (tamaño, posición rotación... del objeto)

  states.texture = &m_tileset;                                                          // Aplicamos la textura (sprite)

  target.draw(m_vertices, states);                                                      // Dibujamos en pantalla el elemento
}
