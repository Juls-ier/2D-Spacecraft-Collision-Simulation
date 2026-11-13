#pragma once
#include <SFML/Graphics.hpp>
#include "Core.h"

class Renderer
{
public:


    void move(bool up, bool down, bool left, bool right);
    
    void scroll(float delta);
    void draw_grid_line(sf::Color color, sf::VertexArray& lines, float x1, float y1, float x2, float y2);
    void draw_point(sf::RenderWindow& window, sf::Color color, float x, float y);
    void draw_line(sf::Color color, sf::VertexArray& lines, float x1, float y1, float x2, float y2);


    void draw(sf::RenderWindow& window, Mesh& mesh);  /// <- ref zeby nie kopiowac vector 

};