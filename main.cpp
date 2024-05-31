

#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "New Witch");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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

