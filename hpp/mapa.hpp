#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>

class Mapa : public sf::Drawable, public sf::Transformable {
  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

  public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, int* tiles, unsigned int ancho, unsigned int alto);
};

#endif
