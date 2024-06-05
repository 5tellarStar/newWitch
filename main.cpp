

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int playerState = 0;

float playerX = 0;
int oldPlayerX = 0;
float playerY = 0;
int oldPlayerY = 0;

int playerDir = 2;

bool animation = false;

bool walking = false;

bool canWalk = true;

int artMap[12][18] = 
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(240, 144), "New Witch");

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Witch.png");
    
    //rect to select sprite from the player spritesheet
    sf::IntRect rectSourcePlayer(0,0,40,40);

    sf::Sprite playerSprite(playerTexture, rectSourcePlayer);

    //clock for players animation
    sf::Clock playerTime;

    //clock to allow turning without walking
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
            //does the player have to turn to walk in this direction
            if(playerDir != 0)
            {
                //turn the player
                playerDir = 0;

                //change to the right sprite
                rectSourcePlayer.left = 640 * playerState;

                //just to get the animation to work correct
                animation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f)
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !walking && canWalk)
        {
            if(playerDir != 1)
            {
                playerDir = 1;

                rectSourcePlayer.left = 160 + 640 * playerState;

                animation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f)
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !walking && canWalk)
        {
            if(playerDir != 2)
            {
                playerDir = 2;

                rectSourcePlayer.left = 320 + 640 * playerState;

                animation = false;
                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f)
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !walking && canWalk)
        {
            if(playerDir != 3)
            {
                playerDir = 3;

                rectSourcePlayer.left = 480 + 640 * playerState;

                animation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f)
            {
                walking = true;
                animation = false;
                playerTime.restart();
            }
        } 


        
        if(walking)
        {
            //moves the player
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
                rectSourcePlayer.left = playerDir * 160 + 640 * playerState;

                //moves the player camera
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
                playerX = oldPlayerX;
                playerY = oldPlayerY;

                walking = false;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.75f && !animation)
            {
                rectSourcePlayer.left = 120 + playerDir * 160 + 640 * playerState;

                animation = true;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.50f && playerTime.getElapsedTime().asSeconds() < 0.75f && animation)
            {
                rectSourcePlayer.left = playerDir * 160 + 640 * playerState;

                animation = false;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.25f && playerTime.getElapsedTime().asSeconds() < 0.50f && !animation)
            {
                rectSourcePlayer.left = 80 + playerDir * 160 + 640 * playerState;
                
                animation = true;
            }
        }
        else
        {
            if (playerTime.getElapsedTime().asSeconds() > 1.0f)
            {
                rectSourcePlayer.left = playerDir * 160 + 640 * playerState;

                playerTime.restart();
                animation = false;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.50f && !animation)
            {
                rectSourcePlayer.left = 40 + playerDir * 160 + 640 * playerState;

                animation = true;
            }
        }











        window.clear();
        playerSprite.setTextureRect(rectSourcePlayer);
        playerSprite.setPosition(sf::Vector2f((7)*16 - 12,(4)*16 - 24));

        sf::RectangleShape tile(sf::Vector2f(16, 16));
        tile.setFillColor(sf::Color::White);

        for(int i = 0; i < 17; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                if (artMap[j-oldPlayerY][i-oldPlayerX] == 1)
                {
                    tile.setPosition(sf::Vector2f((i-playerX-8) * 16, (j-playerY-5) * 16));
                    window.draw(tile);
                }
            }
        }

        window.draw(playerSprite);
        window.display();
        
    }

    return 0;
}

