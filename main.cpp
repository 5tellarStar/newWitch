

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int playerState = 1;

float playerX = 1;
int oldPlayerX = 1;
float playerY = 1;
int oldPlayerY = 1;

int playerDir = 2;

bool playerAnimation = false;

bool walking = false;

bool canWalk = true;

bool bookOpening = false;
bool bookClosing = false;
bool bookOpen = false;
bool turningPageF = false;
bool turningPageB = false;

int openPage = 0;
int pagesFound = 3;

int artUnderMap[12][18] = 
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
int artOverMap[12][18] = 
{
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
int colisionMap[12][18] = 
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(240, 144), "New Witch");
    sf::View view = window.getView();
    view.setCenter(playerX*16,playerY*16);
    window.setView(view);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Witch.png");
    
    //rect to select sprite from the player spritesheet
    sf::IntRect rectSourcePlayer(0,0,40,40);
    sf::Sprite playerSprite(playerTexture, rectSourcePlayer);
    

    sf::Texture bookUITexture;
    bookUITexture.loadFromFile("ShadowBook.png");

    sf::IntRect rectSourceBookUI(0,0,127,101);
    sf::Sprite bookUISprite(bookUITexture, rectSourceBookUI);

    sf::Clock bookTime;

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

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(sf::FloatRect(180,0,9,11).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - view.getCenter() + sf::Vector2f(120,72)) && !bookOpen && !bookOpening && !bookClosing)
            {
                bookOpening = true;
                bookTime.restart();
            }
            else if(sf::FloatRect(180,88,9,13).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - view.getCenter() + sf::Vector2f(120,72)) && bookOpen && !turningPageF && !turningPageB)
            {
                bookClosing = true;
                bookOpen = false;
                bookTime.restart();
            }
            else if(sf::FloatRect(175,1,50,87).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - view.getCenter() + sf::Vector2f(120,72)) && bookOpen && !turningPageF && !turningPageB && openPage - 1 < pagesFound)
            {
                turningPageF = true;
                bookTime.restart();
            }
            else if(sf::FloatRect(125,1,50,87).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - view.getCenter() + sf::Vector2f(120,72)) && bookOpen && !turningPageF && !turningPageB && openPage != 0)
            {
                turningPageB = true;
                bookTime.restart();
            }
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
                playerAnimation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            //if the player doesn't just want to turn and the player can walk there
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f && colisionMap[oldPlayerY - 1][oldPlayerX] == 0)
            {
                walking = true;

                playerAnimation = false;

                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !walking && canWalk)
        {
            if(playerDir != 1)
            {
                playerDir = 1;

                rectSourcePlayer.left = 160 + 640 * playerState;

                playerAnimation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f && colisionMap[oldPlayerY][oldPlayerX + 1] == 0)
            {
                walking = true;

                playerAnimation = false;

                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !walking && canWalk)
        {
            if(playerDir != 2)
            {
                playerDir = 2;

                rectSourcePlayer.left = 320 + 640 * playerState;

                playerAnimation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f && colisionMap[oldPlayerY + 1][oldPlayerX] == 0)
            {
                walking = true;

                playerAnimation = false;

                playerTime.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !walking && canWalk)
        {
            if(playerDir != 3)
            {
                playerDir = 3;

                rectSourcePlayer.left = 480 + 640 * playerState;

                playerAnimation = false;

                playerTime.restart();
                walkDelay.restart();
            }
            else if (walkDelay.getElapsedTime().asSeconds() > 0.15f && colisionMap[oldPlayerY][oldPlayerX - 1] == 0)
            {
                walking = true;

                playerAnimation = false;

                playerTime.restart();
            }
        } 


        if(walking)
        {
            //moves the player in the direction she's facing
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

            //mostly just animation
            if(playerTime.getElapsedTime().asSeconds() > 1.0f)
            {
                rectSourcePlayer.left = playerDir * 160 + 640 * playerState;

                //moves the player
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
            else if (playerTime.getElapsedTime().asSeconds() > 0.75f && !playerAnimation)
            {
                rectSourcePlayer.left = 120 + playerDir * 160 + 640 * playerState;

                playerAnimation = true;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.50f && playerTime.getElapsedTime().asSeconds() < 0.75f && playerAnimation)
            {
                rectSourcePlayer.left = playerDir * 160 + 640 * playerState;

                playerAnimation = false;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.25f && playerTime.getElapsedTime().asSeconds() < 0.50f && !playerAnimation)
            {
                rectSourcePlayer.left = 80 + playerDir * 160 + 640 * playerState;
                
                playerAnimation = true;
            }
        }
        else
        {
            //idle animation
            if (playerTime.getElapsedTime().asSeconds() > 1.0f)
            {
                rectSourcePlayer.left = playerDir * 160 + 640 * playerState;

                playerTime.restart();
                playerAnimation = false;
            }
            else if (playerTime.getElapsedTime().asSeconds() > 0.50f && !playerAnimation)
            {
                rectSourcePlayer.left = 40 + playerDir * 160 + 640 * playerState;

                playerAnimation = true;
            }
        }
        //sets player sprite
        playerSprite.setTextureRect(rectSourcePlayer);

        //sets player position
        playerSprite.setPosition(sf::Vector2f((playerX)*16 - 12,(playerY)*16 - 24));

        //centers the camera on the player
        view.setCenter(clamp(playerX,7.5f,static_cast<float>(sizeof(artUnderMap[0])/sizeof(artUnderMap[0][0])) - 7.5f)*16,clamp(playerY,4.5f,static_cast<float>(sizeof(artUnderMap)/sizeof(artUnderMap[0])) - 4.5f)*16);
        window.setView(view);



        if(bookOpening)
        {
            bookUISprite.setPosition(sf::Vector2f(view.getCenter().x - 8,view.getCenter().y - 162 + 360 * bookTime.getElapsedTime().asSeconds()));

            if(bookTime.getElapsedTime().asSeconds() > 0.25f)
            {
                bookUISprite.setPosition(sf::Vector2f(view.getCenter().x - 8,view.getCenter().y - 72));
                bookOpening = false;
                bookOpen = true;
            }
        }
        else if (bookClosing)
        {
            bookUISprite.setPosition(sf::Vector2f(view.getCenter().x - 8,view.getCenter().y - 72 - 360 * bookTime.getElapsedTime().asSeconds()));

            if(bookTime.getElapsedTime().asSeconds() > 0.25f)
            {
                bookUISprite.setPosition(sf::Vector2f(view.getCenter().x - 8,view.getCenter().y - 162));
                bookClosing = false;
            }
        }
        else if (!bookOpen)
        {
            bookUISprite.setPosition(sf::Vector2f(view.getCenter().x - 8,view.getCenter().y - 162));
            rectSourceBookUI.left = 0;
            openPage = 0;
        }
        else if (bookOpen)
        {
            bookUISprite.setPosition(sf::Vector2f(view.getCenter().x - 8,view.getCenter().y - 72));
        }

        if (turningPageF)
        {
            if(openPage == 0)
            {
                rectSourceBookUI.left = 127 * (static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 1016;
                    turningPageF = false;
                    openPage++;
                }
            }
            else if (openPage == 1 && openPage == pagesFound)
            {
                rectSourceBookUI.left = 1143 + 127 * (static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 2159;
                    turningPageF = false;
                    openPage++;
                }
            }
            else if (openPage == 1)
            {
                rectSourceBookUI.left = 2286 + 127 * (static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 3302;
                    turningPageF = false;
                    openPage++;
                }
            }
            else if (openPage == pagesFound)
            {
                rectSourceBookUI.left = 3429 + 127 * (static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 4445;
                    turningPageF = false;
                    openPage++;
                }
            }
            else
            {
                rectSourceBookUI.left = 4572 + 127 * (static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 5588;
                    turningPageF = false;
                    openPage++;
                }
            }
        }
        else if (turningPageB)
        {
            if(openPage == 1)
            {
                rectSourceBookUI.left = 127 * (8 - static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 0;
                    turningPageB = false;
                    openPage--;
                }
            }
            else if (openPage == 2 && pagesFound == 1)
            {
                rectSourceBookUI.left = 1143 + 127 * (8 - static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 1143;
                    turningPageB = false;
                    openPage--;
                }
            }
            else if (openPage == 2)
            {
                rectSourceBookUI.left = 2286 + 127 * (8 - static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 2286;
                    turningPageB = false;
                    openPage--;
                }
            }
            else if (openPage - 1 == pagesFound)
            {
                rectSourceBookUI.left = 3429 + 127 * (8 - static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 3429;
                    turningPageB = false;
                    openPage--;
                }
            }
            else
            {
                rectSourceBookUI.left = 4572 + 127 * (8 - static_cast<int>(bookTime.getElapsedTime().asSeconds() * 8));
                if (bookTime.getElapsedTime().asSeconds() > 1.0f)
                {
                    rectSourceBookUI.left = 4572;
                    turningPageB = false;
                    openPage--;
                }
            }
        }

        bookUISprite.setTextureRect(rectSourceBookUI);









        //removes last frame
        window.clear();


        sf::RectangleShape tile(sf::Vector2f(16, 16));
        tile.setFillColor(sf::Color::White);
        
        //draws the stuff that's behind the player
        for(int j = 0; j < sizeof(artUnderMap)/sizeof(artUnderMap[0]); j++)
        {
            for(int i = 0; i < sizeof(artUnderMap[0])/sizeof(artUnderMap[0][0]); i++)
            {
                if (artUnderMap[j][i] != 0)
                {
                    tile.setPosition(sf::Vector2f(i * 16, j * 16));
                    window.draw(tile);
                }
            }
        }


        //draws the player
        window.draw(playerSprite);

        //draws the stuff that's in front the player
        for(int j = 0; j < sizeof(artOverMap)/sizeof(artOverMap[0]); j++)
        {
            for(int i = 0; i < sizeof(artOverMap[0])/sizeof(artOverMap[0][0]); i++)
            {
                if (artOverMap[j][i] != 0)
                {
                    tile.setPosition(sf::Vector2f(i * 16, j * 16));
                    window.draw(tile);
                }
            }
        }



        window.draw(bookUISprite);

        //shows the frame
        window.display();
        
    }

    return 0;
}

