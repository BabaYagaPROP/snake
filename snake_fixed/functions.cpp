#include "header.h"

//moving function
void move(Node body[], int direction, sf::Time dt, bool game)
{
    if (game) {
        int step = 100;
        if (direction == 0)
        {
            //moving by step * delta time
            body[0].y -= step * dt.asSeconds();
        }
        else if (direction == 1)
        {
            body[0].x += step * dt.asSeconds();
        }
        else if (direction == 2)
        {
            body[0].y += step * dt.asSeconds();
        }
        else if (direction == 3)
        {
            body[0].x -= step * dt.asSeconds();
        }
    }
}


//eating and earning point function
int eat(Node body[], Node& apple, int& snakeLength, int& score, sf::Sound &point, bool audio)
{
    if (apple.x >= body[0].x - 5 && apple.x <= (body[0].x + 15))
        if (apple.y >= body[0].y - 5 && apple.y <= (body[0].y + 15))
        {
            if(audio)
                point.play();
            score++;
            snakeLength += 10;
            apple.x = std::floor(rand() % 700 / 10) * 10 + 50;
            apple.y = std::floor(rand() % 660 / 10) * 10 + 90;
        }


    return 0;
}

//checking if the game is lost
bool checkGame(Node body[], int snakeLength, int direction,sf::Clock &gameTime, bool game)
{
   
       
    for (int i = snakeLength; i > 0; i--)
    {

        //east
        if (body[0].x + 10 >= body[i].x && body[0].x + 10 <= body[i].x + 10 && direction == 1)
        {
            if (body[0].y >= body[i].y && body[0].y <= body[i].y + 8)
            {
                direction = -1;
                return false;
            }
        }
        //west
        else if (body[0].x - 10 <= body[i].x && body[0].x - 10 >= body[i].x - 10 && direction == 3)
        {
            if (body[0].y >= body[i].y && body[0].y <= body[i].y + 8)
            {
                direction = -1;
                return false;
            }
        }
        //north
        else if (body[0].y - 10 <= body[i].y && body[0].y - 10 >= body[i].y - 10 && direction == 0)
        {
            if (body[0].x >= body[i].x && body[0].x <= body[i].x + 8)
            {
                direction = -1;
                return false;
            }
        }
        //south
        else if (body[0].y + 10 >= body[i].y && body[0].y + 10 <= body[i].y + 10 && direction == 2)
        {
            if (body[0].x >= body[i].x && body[0].x <= body[i].x + 8)
            {
                direction = -1;
                return false;
            }
        }
        else if (body[0].x <= 35 || body[0].x >= 755 || body[0].y <= 75 || body[0].y >= 755)
        {
            direction = -1;
            return false;
        }
        else
            return true;
    }


     
}
//function that keeps the snake in the grid
void roundFunc(Node body[], int direction)
{
    int round;
    if (direction == 0)
        for (int i = 0; i < 5; i++)
        {
            //y is lower so snake goes up
            round = std::floor(body[i].y / 10) * 10;
            body[i].y = round;
            //rounding x
            round = std::round(body[i].x / 10) * 10;
            body[i].x = round;
        }
    else if(direction == 1)
        for (int i = 0; i < 5; i++)
        {
            //x is bigger so snake goes right
            round = std::ceil(body[i].x / 10) * 10;
            body[i].x = round;
            //rounding y
            round = std::round(body[i].y / 10) * 10;
            body[i].y = round;
        }
    else if(direction == 2)
        for (int i = 0; i < 5; i++)
        {
            //y is bigger so snake goes down
            round = std::ceil(body[i].y / 10) * 10;
            body[i].y = round;
            //rounding x
            round = std::round(body[i].x / 10) * 10;
            body[i].x = round;
        }
    else if(direction == 3)
        for (int i = 0; i < 5; i++)
        {
            //x is lower so snake goes left
            round = std::floor(body[i].x / 10) * 10;
            body[i].x = round;
            //rounding y
            round = std::round(body[i].y / 10) * 10;
            body[i].y = round;
        }

}
void gameOver(bool& game, sf::RenderWindow& window, sf::Clock& gameTime, Node body[], int& snakeLength, int& score, int &direction, bool& horizontal, bool& vertical, sf::Clock& deltaClock, sf::Sound& point, bool audio)
{
    sf::Texture tGameOver, tGameOver1, tGameOver2;
    if (!tGameOver.loadFromFile("img/game_over.png"))
        std::cout << "Failed to load game over screen!\n";
    if (!tGameOver1.loadFromFile("img/game_over1.png"))
        std::cout << "Failed to load game over screen!\n";
    if (!tGameOver2.loadFromFile("img/game_over2.png"))
        std::cout << "Failed to load game over screen!\n";
    sf::Sprite gameOver, gameOver1, gameOver2;
    gameOver.setTexture(tGameOver);
    gameOver1.setTexture(tGameOver1);
    gameOver2.setTexture(tGameOver2);
    while (!game)
    {
       
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
        }
        window.clear();
        window.draw(gameOver);

        //play again
        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 550 && sf::Mouse::getPosition(window).y >= 365 && sf::Mouse::getPosition(window).y <= 435) 
        {
            window.draw(gameOver1);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::sleep(sf::seconds(0.3));
                if (audio)
                    point.play();
                for (int i = 1; i <= snakeLength; i++)
                {
                    body[i].x = -20;
                    body[i].y = -20;

                }
                snakeLength = 10;
                body[0].x = 40;
                body[0].y = 80;
                vertical = true;
                horizontal = false;

                gameTime.restart();
                direction = 1;
                score = 0;
                deltaClock.restart();
                game = true;
               
            }
        }
        //quit
        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 550 && sf::Mouse::getPosition(window).y >= 478 && sf::Mouse::getPosition(window).y <= 548) 
        {
            window.draw(gameOver2);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
            {
                if (audio)
                    point.play();
                window.close();
                exit(0);
            }
        }

        window.display();
    }

}
int mainMenu(sf::RenderWindow &window, sf::Music &music, bool &audio, sf::Sound& point)
{
    bool musicSetting = true;
    //main menu
    sf::Texture tMenu0;
    if (!tMenu0.loadFromFile("img/main_menu.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite menu0;
    menu0.setTexture(tMenu0);

    //choice 1
    sf::Texture tMenu1;
    if (!tMenu1.loadFromFile("img/main_menu_1.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite menu1;
    menu1.setTexture(tMenu1);

    //choice 2
    sf::Texture tMenu2;
    if (!tMenu2.loadFromFile("img/main_menu_2.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite menu2;
    menu2.setTexture(tMenu2);

    //choice 3
    sf::Texture tMenu3;
    if (!tMenu3.loadFromFile("img/main_menu_3.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite menu3;
    menu3.setTexture(tMenu3);

    //setings 1
    sf::Texture tSettings;
    if (!tSettings.loadFromFile("img/settings.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite settings;
    settings.setTexture(tSettings);

    //setings 2
    sf::Texture tSettings1;
    if (!tSettings1.loadFromFile("img/settings_back.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite settings1;
    settings1.setTexture(tSettings1);

    //tick
    sf::Texture tickT;
    if (!tickT.loadFromFile("img/tick.png"))
        std::cout << "Faile to load tick texture!\n";
    sf::Sprite tick;
    tick.setTexture(tickT);

    while (true)
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
        }
        //play
        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 550) {
            if (sf::Mouse::getPosition(window).y >= 250 && sf::Mouse::getPosition(window).y <= 320)
            {
                window.clear();
                window.draw(menu1);
                window.display();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (audio)
                        point.play();
                    return 0;
                }

            }
        }
        //settings
        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 550) {
            if (sf::Mouse::getPosition(window).y >= 365 && sf::Mouse::getPosition(window).y <= 435)
            {
                window.clear();
                window.draw(menu2);
                window.display();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (audio)
                        point.play();
                    while (true)
                    {
                        window.clear();
                        window.draw(settings);
                        if (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                            {
                                window.close();
                                exit(0);
                            }
                        }
                        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 550) {
                            if (sf::Mouse::getPosition(window).y >= 478 && sf::Mouse::getPosition(window).y <= 548)
                            { 
                                window.draw(settings1);
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                {
                                    sf::sleep(sf::seconds(0.1));
                                    if (audio)
                                        point.play();
                                    break;
                                }

                            }
                        }
                        if (sf::Mouse::getPosition(window).x >= 500 && sf::Mouse::getPosition(window).x <= 540) {
                            if (sf::Mouse::getPosition(window).y >= 270 && sf::Mouse::getPosition(window).y <= 310) {

                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                {
                                    if (audio)
                                        point.play();
                                    sf::sleep(sf::seconds(0.1));
                                    if (musicSetting)
                                    {
                                        musicSetting = false;
                                        music.pause();
                                    }
                                    else
                                    {
                                        musicSetting = true;
                                        music.play();
                                    }
                                }

                            }
                        }
                        if (sf::Mouse::getPosition(window).x >= 500 && sf::Mouse::getPosition(window).x <= 540) {
                            if (sf::Mouse::getPosition(window).y >= 378 && sf::Mouse::getPosition(window).y <= 420) {

                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                {
                                    if (audio)
                                        point.play();
                                    sf::sleep(sf::seconds(0.1));
                                    if (audio)
                                        audio = false;
                                    else
                                        audio = true;
                                }

                            }
                        }
                        
                        if (audio)
                        {
                            tick.setPosition(500, 380);
                            window.draw(tick);
                        }
                        if (musicSetting)
                        {
                            tick.setPosition(500, 270);
                            window.draw(tick);
                        }
                        
                        window.display();
                    }
                }

            }
        }
        //quit
        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 550)
        {
            if (sf::Mouse::getPosition(window).y >= 478 && sf::Mouse::getPosition(window).y <= 548)
            {
                window.clear();
                window.draw(menu3);
                window.display();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (audio)
                        point.play();
                    window.close();
                    exit(0);
                }
            }
        }
        else
            {
                window.clear();
                window.draw(menu0);
                window.display();
            }
    }
}