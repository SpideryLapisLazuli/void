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
    float R;
    int Mass;
    Planet(Vector2f coord) {
        int rPlanet = 10;
        CircleShape Place(rPlanet);
        Place.setPosition(Vector2f(coord.x-rPlanet,coord.y-rPlanet));
        Place.setFillColor(Color::Blue);
        Vector2f Speed(0,0);
        Vector2f Boost(0,0);
        this->Place = Place;
        this->R = rPlanet;
        this->Position = { Place.getPosition().x + this->R,Place.getPosition().y + this->R };
        this->Speed = Speed;
        this->Mass = 100;

    }
    Planet(Vector2f coord, Vector2f V,int rPlanet,int Mass) {
        CircleShape Place(rPlanet);
        Place.setPosition(Vector2f(coord.x - rPlanet, coord.y - rPlanet));
        Place.setFillColor(Color::Blue);
        Vector2f Speed(V);
        this->Place = Place;
        this->R = rPlanet;
        this->Position = { Place.getPosition().x + this->R,Place.getPosition().y + this->R };
        this->Speed = Speed;
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
        float a, ax, ay, dx, dy, r;
        for (int i = 0; i < Planets.size(); i++) { // считаем текущей
            for (int j = 0; j < Planets.size(); j++) // считаем второй
            {
                if (i == j) continue;
                dx = Planets[j].Position.x - Planets[i].Position.x;
                dy = Planets[j].Position.y - Planets[i].Position.y;

                r = dx * dx + dy * dy;// тут R^2
                if (r == 0) r = 1; // избегаем деления на очень маленькое число
                a = Planets[j].Mass / r;

                r = sqrt(r); // тут R

                ax = a * (dx / r); // a * cos
                ay = a * (dy / r); // a * sin
                Planets[i].Speed.x += ax;
                Planets[i].Speed.y += ay;
            }
            // координаты меняем позже, потому что они влияют на вычисление ускорения
            }
        for (int i = 0; i < Planets.size(); i++) {
            Planets[i].Position = { Planets[i].Position.x + Planets[i].Speed.x, Planets[i].Position.y + Planets[i].Speed.y };
            Planets[i].Place.setPosition(Planets[i].Position.x - Planets[i].R, Planets[i].Position.y - Planets[i].R);
        }
            for (int i = 0; i < Planets.size(); i++) {
                for (int j = 0; j < Planets.size(); j++) { 
                    if (i == j) continue;
                    blind(i,j);
                }
            }

    }
    void blind(int i, int j) {
        float dx, dy, r;
        dx = Planets[j].Position.x - Planets[i].Position.x;
        dy = Planets[j].Position.y - Planets[i].Position.y;

        r = dx * dx + dy * dy;

        if (r < Planets[i].R * 10 + Planets[j].R * 10) {
            Planets[i].Position.x = (Planets[i].Position.x + Planets[j].Position.x) / 2.0;
            Planets[i].Position.y = (Planets[i].Position.y + Planets[j].Position.y) / 2.0;
            Planets[i].Speed.x = (Planets[i].Speed.x * Planets[i].Mass + Planets[j].Speed.x * Planets[j].Mass) / (Planets[j].Mass + Planets[i].Mass);
            Planets[i].Speed.y = (Planets[i].Speed.y * Planets[i].Mass + Planets[j].Speed.y * Planets[j].Mass) / (Planets[j].Mass + Planets[i].Mass);
            Planets[i].Mass += Planets[j].Mass;
            Planets[i].R += Planets[j].R;
            Planet p(Planets[i].Position, Planets[i].Speed, Planets[i].R, Planets[i].Mass);
            Planets[i] = p;
            Planets.erase(Planets.begin() + j);
        }
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
                    Planet p(Vector2f(sf::Mouse::getPosition(window)));
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