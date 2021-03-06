// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UI/Text.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Scene.h"

const int resX = 1200;
const int resY = 800;

double DeltaTime = 0.016666667;

int main()
{
    sf::RenderWindow window(sf::VideoMode(resX, resY), "UI");

    InitialisizeScenes();

    sf::Clock Clock;

    while (window.isOpen())
    {
        DeltaTime = (Clock.getElapsedTime()).asSeconds();
        Clock.restart();
        window.clear(sf::Color(150,150,150));
        SceneManager[CurrentSceneIndex]->Animate(window, DeltaTime);
        window.display();
    }
    for (int i = 0; i < SceneManager.size(); i++) {
        delete SceneManager[i];
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
