#include "App.h"

App::App()
    : window(sf::VideoMode(1200, 800), "Geometria")
{


    //mesh.create_object("ksztalt_2.txt");
   // mesh.create_object("ksztalt_3.txt");
  
    mesh.create_object("craft1_ksztalt.txt", "space_craft1.txt");
    mesh.load_missiles("missiles2.txt");
    mesh.check_collision();





}

void App::run()
{

    sf::Clock clock;
    int steps = 0;

    
    while (window.isOpen())
    {
        sf::Event event;



        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::MouseWheelScrolled) {
                renderer.scroll(event.mouseWheelScroll.delta);
            }


            if (event.type == sf::Event::Closed) {
                window.close();
            }
        
        
        
        }


            if (steps < 20 && clock.getElapsedTime().asSeconds() >= 0.1f)
            {
                clock.restart();
                steps++;

                mesh.objects[0]->update_position();
                

                for (int i = 0; i < mesh.missiles.size(); i++) {

                    if (mesh.missiles[i].time < steps*0.1) {
                        double time_after_found =   0.1*steps - mesh.missiles[i].time;
                        mesh.missiles[i].update_position(time_after_found);
                        mesh.missiles[i].time = 0.1 * steps;
                        mesh.missiles[i].draw = true;

                    }
                    


                }

                for (int i = 0; i < mesh.collisions.size(); i++) {


                    if (mesh.collisions[i].time < steps * 0.1) {
                        double time_after_found = 0.1 * steps - mesh.missiles[i].time;
                        mesh.collisions[i].draw = true;

                       if (time_after_found < 0.1 && time_after_found>0) {

                            mesh.update_collision(mesh.collisions[i], mesh.objects[0]->velocity, time_after_found);
                        }
                       else {
                           mesh.update_collision(mesh.collisions[i], mesh.objects[0]->velocity, 0.1);

                       }
                    }

                    

                   


                }



            }
        


        render();
    }

}


void App::input_reader() {


    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    renderer.move(up, down, left, right);


}



void App::render()
{
  
    input_reader();
    window.clear(sf::Color(10, 10, 20));
    renderer.draw(window, mesh);
    window.display();
}

