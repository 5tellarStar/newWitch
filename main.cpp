

#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(240, 144), "New Witch");

    sf::Texture texture;
    texture.loadFromFile("Witch.png");
    
    sf::IntRect rectSourceSprite(1920,0,40,40);
    sf::Sprite sprite(texture, rectSourceSprite);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(clock.getElapsedTime().asSeconds() > 1.0f)
        {
            if (rectSourceSprite.left == 1960)
            {
                rectSourceSprite.left = 0;
            }
            else
                rectSourceSprite.left += 40;

            sprite.setTextureRect(rectSourceSprite);
            clock.restart();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

