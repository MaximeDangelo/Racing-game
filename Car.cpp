#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Car.h"

using namespace std;
using namespace sf;

Car::Car(sf::Vector2f position)
{
    this->ready = false;

    monImage.loadFromFile("ff_PNG_final.png");

    if (!texture.loadFromImage(monImage))
    {
        std::cerr << "Erreur de conversion d'image en texture" << endl;
    }
    else
    {
        monSprite.setTexture(texture);
        monSprite.setPosition(position);
        sf::FloatRect rectangle = monSprite.getLocalBounds();
        monSprite.setOrigin(rectangle.width / 2, rectangle.height / 2);
    }
    speed = 0;
    x = 0;
    y = 0;
    angle = 0;
    n = 0;

    acc = 0.2;
    dec = 0.3;
    maxSpeed = 6.0;
    minSpeed = -12.0;
    turnSpeed = 0.1;

}

Car::~Car()
{
    // destructeur
}

Sprite Car::GetSprite()
{
    return monSprite;
}

void Car::setDirection(float newAngle)
{
    angle = newAngle;
    directionX = std::cos(angle);
    directionY = std::sin(angle);
}

float Car::getDirectionX() const
{
    return directionX;
}

float Car::getDirectionY() const
{
    return directionY;
}
void Car::Avancer()
{
    float angle = monSprite.getRotation() * 3.1415 / 180;

    monSprite.move(sf::Vector2f(speed * sin(angle), -speed * cos(angle)));

}
void Car::ToutDroit()      //if Up 
{
    if (speed < maxSpeed)
        if (speed < 0)  speed -= dec;
        else speed += acc;

}

void Car::Reculer()            //if Down
{
    if (speed > minSpeed)
        if (speed > 0) speed -= dec;
        else  speed -= acc;
}

void Car::TournerDroite()        //if Right
{
    monSprite.setRotation(monSprite.getRotation() + 5);// turnSpeed* speed / maxSpeed);


}

void Car::TournerGauche()        //if Left
{
    if (speed != 0)
        monSprite.setRotation(monSprite.getRotation() - 5);
}

void Car::Decelerer()              // if aucun bouton
{
    if (speed - dec > 0) speed -= dec;
    else if (speed + dec < 0) speed += dec;
    else speed = 0;
}

void Car::Decelerer2()              // if aucun bouton
{
    if (speed - dec > 0) speed -= dec;
    else if (speed + dec < 0) speed += dec;
    else speed = 0;
}


void Car::ChangeVitesse()
{
    if (speed > 0.2)
    {
        speed -= 0.2;
    }

}