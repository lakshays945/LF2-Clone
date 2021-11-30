#include <SFML/Graphics.hpp>
#include <bandit.h>

static double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;
int main(){
    sf::RenderWindow window(sf::VideoMode(resX, resY), "Little Fighter 2");
    Bandit Player;
    sf::Clock Clock;
    while (window.isOpen()){
        DeltaTime = (Clock.getElapsedTime()).asSeconds();
        Clock.restart();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    Player.Up = 1;
                    break;
                case sf::Keyboard::S:
                    Player.Down = 1;
                    break;
                case sf::Keyboard::A:
                    Player.Left = 1;
                    break;
                case sf::Keyboard::D:
                    Player.Right = 1;
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    Player.Up = 0;
                    break;
                case sf::Keyboard::S:
                    Player.Down = 0;
                    break;
                case sf::Keyboard::A:
                    Player.Left = 0;
                    break;
                case sf::Keyboard::D:
                    Player.Right = 0;
                    break;
                default:
                    break;
                }
            }
        }
        Player.AddForce(DeltaTime);
        Player.Translate(DeltaTime);
        window.clear(sf::Color(50, 60, 30));
        Player.Animate(window);
        window.display();
    }
    return 0;
}