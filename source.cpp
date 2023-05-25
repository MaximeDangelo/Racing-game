#include "SFML/Graphics.hpp" 
#include "SFML/System.hpp" 
#include "SFML/Window.hpp" 
#include "SFML/Audio.hpp" 
#include "SFML/Network.hpp" 

#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include "Car.h"


using namespace sf;



const float MAX_DRIFT_ANGLE = 45.0f; // Maximum angle for drifting
const float DRIFT_FORCE = 10.0f;     // Force applied during drifting

bool Up = false, Right = false, Down = false, Left = false, Drift = false;



Car* ajout_joueur()
{
    Car* j = NULL;
    std::string nom;
    std::cout << "Entrez votre nom : ";
    getline(std::cin >> std::ws, nom);
    char c;
    std::cout << "Entrez votre Couleur (r) Rouge, (b) Bleu ";
    std::cin >> c;
    switch (c)
    {
    case 'r':
        j = new Car(sf::Vector2f(400, 400));
        break;
    case 'b':
        j = new Car(sf::Vector2f(400, 300));
        break;

    }

    return j;
}

int main()
{
    RenderWindow app(VideoMode(1440, 1080), "C'est parti !");
    app.setFramerateLimit(60);
    std::vector<Car*> mes_voit;
    for (int i = 0; i < mes_voit.size(); i++)
    {
        mes_voit.push_back(new Car(sf::Vector2f(200, 200)));
    }
    Car* voit1, * voit2;

    for (int i = 0; i < mes_voit.size(); i++)
    {
        std::cout << "Joueur  : " << i + 1 << std::endl;
        mes_voit[i] = ajout_joueur();
    }


    std::cout << std::endl;







    Texture green, track, monSprite;
    sf::Image img;
    img.loadFromFile("XD/Circuit_Hitbox.png");
    track.loadFromImage(img);
    green.loadFromFile("XD/backgroundimage.png");

    track.setSmooth(true);             //lissage pour rendre moins pixelisé




    sf::Color green_color(18, 255, 0);//couleur route

    Sprite sBackground(track), qBackground(green), sCar;
    //sf::Vector2f pos_in(400, 400);
    //Car mavoit(pos_in);
    sBackground.scale(1, 1);
    qBackground.scale(1, 1);

    //monSprite.setOrigin(0, 0);                 //Point de départ de la caisse
    float R = 22;

    const int N = 5;



    sf::Clock time;

    sf::Font font;
    if (!font.loadFromFile("XD/Dosis-Light.ttf"))
        return EXIT_FAILURE;

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(50, 30);

    sf::Clock clock;
    sf::Time elapsedTime;
    int seconds = 0;

    //= ====== = Ajoute musique BUG OpenAl32.ddl====== =
        /* sf::SoundBuffer buffer;
         if (!buffer.loadFromFile("XD/audi-v8-acceleration-sound-6067.ogg"))
         {

         }
         sf::Sound sound1;
         sound1.setBuffer(buffer);
         sound1.play();*/



    while (app.isOpen())
    {
        for (int i = 0; i < mes_voit.size(); i++)
        {
            sf::FloatRect recta = mes_voit[i]->GetSprite().getGlobalBounds();
            Color c = img.getPixel(recta.left, recta.top);
            sf::Color color_at_car = c;    //sortie de piste
            if (color_at_car != green_color)
            {

                mes_voit[i]->ChangeVitesse();
            }





            //if (c.g == 255)

            std::cout << (int)c.r << "  " << (int)c.g << "  " << (int)c.b << std::endl;

            float deltaTime;
            Event e;
            while (app.pollEvent(e))
            {
                switch (e.type)
                {
                case sf::Event::Closed:
                    app.close();

                case sf::Event::EventType::KeyPressed:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::D:
                        Right = true;
                        break;
                    case sf::Keyboard::Z:
                        Up = true;
                        break;
                    case sf::Keyboard::Q:
                        Left = true;
                        break;
                    case sf::Keyboard::S:
                        Down = true;
                        break;
                    }
                    break;
                case sf::Event::EventType::KeyReleased:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::D:
                        Right = false;
                        break;
                    case sf::Keyboard::Z:
                        Up = false;
                        break;
                    case sf::Keyboard::Q:
                        Left = false;
                        break;
                    case sf::Keyboard::S:
                        Down = false;
                        break;
                    }


                }
            }
            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed;
            mes_voit[i]->Avancer();


            if (Up)
            {
                mes_voit[i]->ToutDroit();
            }
            if (Down)
            {
                mes_voit[i]->Reculer();
            }
            if (Right && Up)
            {
                mes_voit[i]->TournerDroite();
            }
            if (Left && Up)
            {
                mes_voit[i]->TournerGauche();
            }
            if (Right && Down)
            {
                mes_voit[i]->TournerGauche();
            }
            if (Left && Down)
            {
                mes_voit[i]->TournerDroite();
            }
            if (!Up && !Down)                   //Décéleration si l'on n'accélère pas
            {
                mes_voit[i]->Decelerer();
            }
            if (!Down && !Up)                   //Décéleration si l'on n'accélère pas
            {
                mes_voit[i]->Decelerer2();
            }




            //mes_voit[i]->setDirection(45.0f); // Définir l'angle de direction de la voiture

            //float directionX = mes_voit[i]->getDirectionX(); // Obtenir la composante x de la direction
            //float directionY = mes_voit[i]->getDirectionY(); // Obtenir la composante y de la direction

            //// Utiliser les composantes de direction pour effectuer des calculs ou des opérations
            //float newX = mes_voit[i]->x + directionX * car[i]->speed;
            //float newY = mes_voit[i]->y + directionY * car[i]->speed;


            //mavoit.move();









            app.clear(Color::Blue);



            // qBackground.setPosition(-offsetX, -offsetY);              //Dessiner mes Backgrounds
            app.draw(sBackground);
            // sBackground.setPosition(-offsetX, -offsetY);
            app.draw(qBackground);

            //sCar.setPosition(-offsetX, -offsetY);
            /* for (int i = 0; i < car.size(); i++)
             {
                 app.draw(car[i]->GetSprite());
             }*/
            app.draw(mes_voit[i]->GetSprite());
            // app.draw(car[0]->GetSprite());
        }


        app.display();
    }
    int taille = mes_voit.size();
    for (int i = 0; i < taille; i++)
    {
        delete mes_voit.back();
        mes_voit.pop_back();
    }
    return 0;
}







// Rajouter 2ème voiture

