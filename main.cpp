

#include <SFML/Graphics.hpp>
float screenWidth = 240.f;
float screenHeight = 144.f;


int main()
{
    sf::RenderWindow window(sf::VideoMode(240, 144), "New Witch");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                sf::Vector2u size = window.getSize();

                float heightRatio = screenHeight / screenWidth;
                float widthRatio = screenWidth / screenHeight;

                if (size.y * widthRatio <= size.x)
                {
                    size.x = size.y * widthRatio;
                }
                else if (size.x * heightRatio <= size.y)
                {
                    size.y = size.x * heightRatio;
                }

                window.setSize(size);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            shape.setFillColor(sf::Color::Red);
        }
        else
        {
            shape.setFillColor(sf::Color::Green);
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

