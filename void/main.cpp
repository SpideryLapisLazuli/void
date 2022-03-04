#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
using namespace sf;
class Game;
struct Planet {
    CircleShape Place;
    Vector2f Position;
    Vector2f Speed;
    Vector2f Boost;
    int Mass;
    Planet(Vector2i coord) {
        int rPlanet = 10;
        CircleShape Place(rPlanet);
        Place.setPosition(Vector2f(coord.x-rPlanet,coord.y-rPlanet));
        Place.setFillColor(Color::Blue);
        Vector2f Speed(0,0);
        Vector2f Boost(0,0);
        this->Place = Place;
        this->Position = Place.getPosition();
        this->Speed = Speed;
        this->Boost = Boost;
        this->Mass = 100;

    }
    Planet(Vector2i coord, Vector2f V, Vector2f a,int rPlanet,int Mass) {
        CircleShape Place(rPlanet);
        Place.setPosition(Vector2f(coord.x - rPlanet, coord.y - rPlanet));
        Place.setFillColor(Color::Blue);
        Vector2f Speed(V);
        Vector2f Boost(a);
        this->Place = Place;
        this->Position = Place.getPosition();
        this->Speed = Speed;
        this->Boost = Boost;
        this->Mass = Mass;

    }};
class Game {
    sf::RenderWindow window{ sf::VideoMode(sf::VideoMode::getDesktopMode()), "void" };
    std::vector<Planet> Planets;
    void Drow() {
        for (size_t i = 0; i < Planets.size(); i++) {
            window.draw(Planets[i].Place);
        }
    }
    void Physics() {
        for (size_t i = 0; i < Planets.size(); i++) {
            for (int j = 0; j < Planets.size(); j++) {
                if (j == i) continue;
                float B = Planets[j].Mass / Distance(Planets[i].Position, Planets[j].Position);
                //if (B != B) continue;
                float hvjh = B*Direction(Planets[i].Position, Planets[j].Position).x;
                Planets[i].Boost.x += B *Direction(Planets[i].Position, Planets[j].Position).x;
                Planets[i].Boost.y += B *Direction(Planets[i].Position, Planets[j].Position).y;
            }
        }
        for (int i = 0; i < Planets.size(); i++) {
            Planets[i].Speed.x += Planets[i].Boost.x;
            Planets[i].Speed.y += Planets[i].Boost.y;
            Planets[i].Boost = { 0,0 };
            Planets[i].Position = { Planets[i].Position.x + Planets[i].Speed.x, Planets[i].Position.y + Planets[i].Speed.y };
                for (int j = 0; j < Planets.size(); j++) {
                    if (j == i) continue;
                    Debag(Planets[i].Place.getPosition(), Planets[j].Place.getPosition(), Planets[i].Position, Planets[j].Position);
                }
            Planets[i].Place.setPosition(Planets[i].Position);
        }
    }
    void Debag(sf::Vector2f First0, sf::Vector2f Second0, sf::Vector2f Firstx, sf::Vector2f Secondx){//не рабочая хрень, которая в теории должна была все исправить
        if (First0.x > Second0.x && Firstx.x < Secondx.x) Secondx.x = First0.x; Firstx.x = Second0.x;
        if (First0.y > Second0.y && Firstx.y < Secondx.y) Firstx.y = Second0.y; First0.y = Secondx.y;
    }
    float Distance(sf::Vector2f First, sf::Vector2f Second) {
        float x = (Second.x - First.x);
        float y = (Second.x - First.x);
        if (x < 0) x *= -1;
        if (y < 0) y *= -1;
        float p = x * x + y * y;
        if (p <= 1) p = 1;
        return p;
    }
    sf::Vector2f Direction(sf::Vector2f First, sf::Vector2f Second) {
        float x = Second.x - First.x;
        float y = Second.y - First.y;
        if (x < 0) x *= -1;
        if (y < 0) y *= -1;
        if (x == 0 && y == 0) x = 1;
        sf::Vector2f DirWeights(((Second.x - First.x) / (x + y)), ((Second.y - First.y) / (x + y)));
        return DirWeights;
    }
public:
    void play()
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    Planet p(sf::Mouse::getPosition(window));
                    Planets.push_back(p);
                }
            }
            window.clear(sf::Color(0, 0, 0, 0));
            Physics();
            Drow();
            window.display();
            Sleep(50);
        }
    }
};
int main()

{
    Game g;
    g.play();
    return 0;

}