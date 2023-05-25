#pragma once

#include <SFML/Graphics.hpp>
class Car
{
public:

    Car(sf::Vector2f position);                 //load l'image là dedans 
    sf::Sprite GetSprite();


    void setDirection(float newAngle);
    float getDirectionX() const;
    float getDirectionY() const;

    void ToutDroit();
    void Reculer();
    void TournerDroite();
    void TournerGauche();
    void Decelerer();
    void Decelerer2();
    void Avancer();
    void ChangeVitesse();

    //void move();

    int directionX = 0.0f; // Initialiser directionX à 0
    int directionY = 0.0f; // Initialiser directionY à 0

    virtual ~Car();

private:
    sf::Texture texture;
    sf::Image monImage;
    sf::Sprite monSprite;


    float x, y, speed, angle, acc, dec, maxSpeed, minSpeed, turnSpeed;
    int n;

    bool ready;

};
