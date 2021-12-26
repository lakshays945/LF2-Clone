#include <SFML/Graphics.hpp>
#include "Players/bandit.h"
static double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;
int main(){
    sf::Texture BGTex;
    sf::Sprite BGSpr;
    BGTex.loadFromFile("src/Resource/BG1.png");
    BGSpr.setTexture(BGTex);
    BGSpr.setPosition(sf::Vector2f(0, 0));
    BGSpr.setScale(sf::Vector2f(1.5, 1.6));
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
                Player.Input_Manager.GetInputDown(event.key.code);
            }
            if (event.type == sf::Event::KeyReleased) {
                Player.Input_Manager.GetInputUp(event.key.code);
            }
        }
        window.clear(sf::Color(50, 60, 30));
        window.draw(BGSpr);
        Player.Update(DeltaTime, window);
        window.display();
    }
    return 0;
}