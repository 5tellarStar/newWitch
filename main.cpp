

#include <SFML/Graphics.hpp>

int playerState = 0;

int map[][] = 
{
    {1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(240, 144), "New Witch");

    sf::Texture texture;
    texture.loadFromFile("Witch.png");
    
    sf::IntRect rectSourcePlayer(1920,0,40,40);
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
            if (rectSourcePlayer.left == 1960)
            {
                rectSourcePlayer.left = 0;
            }
            else
                rectSourcePlayer.left += 40;

            sprite.setTextureRect(rectSourcePlayer);
            clock.restart();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

