#include "Renderer.h"


float offset_x = -300;
float offset_y = 200;

float X0 = 600;
float Y0 = 400;


float moveset = 20;


int spacing = 1;


float zoom = 1.0f;

void Renderer::move(bool up, bool down, bool left, bool right) {


    if (up) {
        offset_y += moveset; 
    }
    if (down) {
        offset_y -= moveset; 
    }
    if (left) {
        offset_x += moveset; 
    }
    if (right) {
        offset_x -= moveset;
    }

   

}

void Renderer::scroll(float delta) {

    spacing +=delta;

}



void Renderer::draw_grid_line(sf::Color color, sf::VertexArray& lines, float x1, float y1, float x2, float y2) {

    lines.append(sf::Vertex(sf::Vector2f(x1 + offset_x, y1 + offset_y), color));
    lines.append(sf::Vertex(sf::Vector2f(x2 + offset_x, y2 + offset_y), color));


}


void Renderer::draw_point(sf::RenderWindow& window, sf::Color color,  float x, float y){


    sf::CircleShape point(5);
    point.setOrigin(5, 5);
    point.setFillColor(color);
    point.setPosition(X0+x*spacing + offset_x, Y0 -y*spacing + offset_y);
    window.draw(point);


}




void Renderer::draw_line(sf::Color color, sf::VertexArray& lines, float x1, float y1, float x2, float y2) {

    lines.append(sf::Vertex(sf::Vector2f(X0+ (x1*spacing) +offset_x, Y0- (y1* spacing) +offset_y), color));
    lines.append(sf::Vertex(sf::Vector2f(X0+ (x2*spacing) +offset_x, Y0 - (y2* spacing) +offset_y), color));


}









void Renderer::draw(sf::RenderWindow& window, Mesh& mesh)
{

    // siatka


    sf::VertexArray grid(sf::Lines);
    sf::Color color_grid(40, 60, 90);
    sf::Color color_oxy(70, 120, 180);

    
   

    for (int i = X0; i <= 3000; i += spacing) {
        draw_grid_line(color_grid, grid, i, Y0 +1500, i, Y0  - 1500);
        draw_grid_line(color_grid, grid, 2*X0-i, Y0  + 1500, 2*X0-i, Y0  - 1500);
    } 


    for (int i = Y0; i <= 3000; i += spacing) {
        draw_grid_line(color_grid, grid, X0+1500, i, X0-1500, i);
        draw_grid_line(color_grid, grid, X0 + 1500, 2*Y0 - i, X0 - 1500, 2 * Y0 - i);
    }

    
    window.draw(grid);


    //draw_grid_line(color_oxy, grid, 0, 400, 1200, 400);   ///osie
    //draw_grid_line(color_oxy, grid, 600, 0, 600, 800);

  
    /// punkty sprawdzenie wczytu i poprawnosci otoczki

    sf::Color basic_point(0, 200, 255);
    sf::Color mean_point(200, 100, 255, 80);

    for (int i = 0; i < mesh.objects[0]->points.size(); i++) {

        draw_point(window, basic_point,  mesh.objects[0]->points[i].x, mesh.objects[0]->points[i].y);

    }


    for (int i = 0; i < mesh.objects[0]->convex.size(); i++) {

        draw_point(window, mean_point, mesh.objects[0]->convex[i].x, mesh.objects[0]->convex[i].y);

    }
    /// elementy ( wiec i linie ) 



    sf::VertexArray element_lines(sf::Lines);

   
    for (int j = 0; j < mesh.objects[0]-> convex.size(); j++) {


        if (j + 1 < mesh.objects[0]->convex.size()) {
            draw_line(mean_point, element_lines, mesh.objects[0]->convex[j].x, mesh.objects[0]->convex[j].y, mesh.objects[0]->convex[j+1].x, mesh.objects[0]->convex[j+1].y);
        }
        else {

            draw_line(mean_point, element_lines,

                mesh.objects[0]->convex[j].x, mesh.objects[0]->convex[j].y, mesh.objects[0]->convex[0].x, mesh.objects[0]->convex[0].y);

        }

        window.draw(element_lines);


    }
    
    sf::Color space_red(220, 20, 60);

    for (int i = 0; i < mesh.missiles.size(); i++) {
        if (mesh.missiles[i].draw == true) {
            draw_point(window, space_red, mesh.missiles[i].base_position.x, mesh.missiles[i].base_position.y);
        }
    }

    sf::Color laser_red(255, 0, 0);

    for (int i = 0; i < mesh.collisions.size(); i++) {
        if (mesh.collisions[i].draw == true) {
            draw_point(window, space_red, mesh.collisions[i].position.x, mesh.collisions[i].position.y);
        }
    }

    ///


    


   
}


