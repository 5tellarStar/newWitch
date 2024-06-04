

#include <SFML/Graphics.hpp>

int playerState = 0;

float playerX = 3;
int oldPlayerX = 3;
float playerY = 5;
int oldPlayerY = 5;

int playerDir = 2;

bool animation = false;

bool walking = false;

bool canWalk = true;

int map[6][10] = 
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(240, 144), "New Witch");

    sf::Texture texture;
    texture.loadFromFile("Witch.png");
    
    sf::IntRect rectSourcePlayer(1280,0,40,40);
    sf::Sprite playerSprite(texture, rectSourcePlayer);
    sf::Clock playerTime;
    sf::Clock walkDelay;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !walking && canWalk)
        {
            if(playerDir != 0 || walkDelay.getElapsedTime().asSeconds() < 0.1f)
            {
                playerDir = 0;
                switch (playerState)
                {
                case 0:
                    rectSourcePlayer.left = 1400;
                    break;
            
                default:
                    break;
                }
                walkDelay.restart();
            }
            else
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !walking && canWalk)
        {
            if(playerDir != 1 || walkDelay.getElapsedTime().asSeconds() < 0.1f)
            {
                playerDir = 1;
                switch (playerState)
                {
                case 0:
                    rectSourcePlayer.left = 1520;
                    break;
                default:
                    break;
                }
                walkDelay.restart();
            }
            else
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !walking && canWalk)
        {
            if(playerDir != 2 || walkDelay.getElapsedTime().asSeconds() < 0.1f)
            {
                playerDir = 2;
                switch (playerState)
                {
                case 0:
                    rectSourcePlayer.left = 1280;
                    break;
            
                default:
                    break;
                }
                walkDelay.restart();
            }
            else
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !walking && canWalk)
        {
            if(playerDir != 3 || walkDelay.getElapsedTime().asSeconds() < 0.1f)
            {
                playerDir = 3;
                switch (playerState)
                {
                case 0:
                    rectSourcePlayer.left = 1640;
                    break;
            
                default:
                break;
                }
                walkDelay.restart();
            }
            else
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        } 

        switch (playerState)
        {
        case 0:
            if(walking)
            {
                switch (playerDir)
                {
                case 0:
                    playerY = oldPlayerY - playerTime.getElapsedTime().asSeconds();
                    break;
                case 1:
                    playerX = oldPlayerX + playerTime.getElapsedTime().asSeconds();
                    break;
                case 2:
                    playerY = oldPlayerY + playerTime.getElapsedTime().asSeconds();
                    break;
                case 3:
                    playerX = oldPlayerX - playerTime.getElapsedTime().asSeconds();
                    break;
                default:
                    break;
                }

                if(playerTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourcePlayer.left -= 80;
                    switch (playerDir)
                    {
                    case 0:
                        oldPlayerY--;
                        break;
                    case 1:
                        oldPlayerX++;
                        break;
                    case 2:
                        oldPlayerY++;
                        break;
                    case 3:
                        oldPlayerX--;
                        break;
                    
                    default:
                        break;
                    }
                    playerY = oldPlayerY;
                    walking = false;
                }
                else if (playerTime.getElapsedTime().asSeconds() > 0.75f && !animation)
                {
                    rectSourcePlayer.left += 80;
                    animation = true;
                }
                else if (playerTime.getElapsedTime().asSeconds() > 0.50f && playerTime.getElapsedTime().asSeconds() < 0.75f && animation)
                {
                    rectSourcePlayer.left -= 40;
                    animation = false;
                }
                else if (playerTime.getElapsedTime().asSeconds() > 0.25f && playerTime.getElapsedTime().asSeconds() < 0.50f && !animation)
                {
                    rectSourcePlayer.left += 40;
                    animation = true;
                }
            }
            break;
        
        default:
            break;
        }




        /*
        if(playerTime.getElapsedTime().asSeconds() > 1.0f)
        {
            if (rectSourcePlayer.left == 1960)
            {
                rectSourcePlayer.left = 0;
            }
            else
                rectSourcePlayer.left += 40;

            playerSprite.setTextureRect(rectSourcePlayer);
            playerTime.restart();
        }
        */









        window.clear();
        playerSprite.setTextureRect(rectSourcePlayer);
        playerSprite.setPosition(sf::Vector2f(playerX*24 - 8,playerY*24 - 20));

        sf::RectangleShape tile(sf::Vector2f(24, 24));
        tile.setFillColor(sf::Color::White);

        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 6; j++)
            {
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
                {
                    tile.setPosition(sf::Vector2f(i * 24, j * 24));
                    window.draw(tile);
                }
            }
        }

        window.draw(playerSprite);
        window.display();
        
    }

    return 0;
}

