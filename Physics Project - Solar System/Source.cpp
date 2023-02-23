#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <numeric>
#include "Renderer.h"
#include "PhysicsWorld.h"
#include "Vector2d.h"

using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

PhysicsWorld world;

int main()
{
    Renderer renderer;
    Clock clock, timer;
    float dt = 0;

    Particle Sun(Vector2d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 100, 50, Vector2d(0, 0), 1);
    Sun.circleBody.setFillColor(sf::Color::Yellow);
    Particle P1 = Particle(Vector2d(350, SCREEN_HEIGHT / 2), 75, 20, Vector2d(1, 1));
    Particle P2 = Particle(Vector2d(SCREEN_WIDTH - 350, SCREEN_HEIGHT / 2), 75, 20, Vector2d(-1, 1));
    list<Particle> celestialBodies;

    float gravitationalForceFactor = 10, gravitationalForcePower = 11.15;
    float velocity = 9;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!"/*, sf::Style::Fullscreen*/);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse get position
            sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asSeconds() > 0.2f) {
                srand(time(NULL));
                int radius = 15;
                int XradnomVelocity = rand() % 2 - 1;
                int YradnomVelocity = rand() % 2 - 1;
                while (XradnomVelocity == 0)    XradnomVelocity = rand() % 2 - 1;
                while (YradnomVelocity == 0)    YradnomVelocity = rand() % 2 - 1;
                bool vertical = (mousePosition.y > 405 && mousePosition.y < 675);
                if (vertical == true){
                    Particle temp = Particle(Vector2d(mousePosition.x, mousePosition.y), 10, radius, Vector2d(0, YradnomVelocity * velocity));
                    celestialBodies.push_back(temp);
                }
                else {
                    Particle temp = Particle(Vector2d(mousePosition.x, mousePosition.y), 200, radius, Vector2d(XradnomVelocity * velocity, 0));
                    celestialBodies.push_back(temp);
                }
                timer.restart();
            }
        }

        // Update World
        if (clock.getElapsedTime().asSeconds() >= 0.0167){
            world.ClearList();
            renderer.ClearDrawables();
         
            //Adds particles to the world;
            world.addParticle(&Sun);
            world.addParticle(&P1);
            world.addParticle(&P2);

            list<Particle>::iterator it;
            list<Particle>::iterator begin = celestialBodies.begin();
            list<Particle>::iterator end = celestialBodies.end();
            for (it = begin; it != end; it++) {
                world.addParticle(&(*it));
            }
                
            for (int i = 0; i < world.listOfWorldParticles.size(); i++){
                list<Particle*>::iterator it;
                list<Particle*>::iterator begin = world.listOfWorldParticles.begin();
                list<Particle*>::iterator end = world.listOfWorldParticles.end();
                for (it = begin; it != end; it++){
                    (*it)->ForceFromOtherParticles(world.listOfWorldParticles, pow(gravitationalForceFactor, gravitationalForcePower));
                    renderer.AddDrawable(&(*it)->circleBody);
                }
            }
            clock.restart();
            world.Update(0.1);
        }
        renderer.Render(&window);
    }
    return 0;
}