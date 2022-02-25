#include "header.h"
#include <Windows.h>

int main()
{
   
    srand(time(NULL));

    //window 
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    if(::IsWindowVisible(::GetConsoleWindow()))
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    //music
    sf::SoundBuffer pointB;
    sf::Sound  point;
    sf::Music music;
    bool audio = true;

    if (!music.openFromFile("audio/music.wav"))
        return -1; // error
    music.play();
    if (!pointB.loadFromFile("audio/point.wav"))
        std::cout << "failed to load music!\n";

    point.setBuffer(pointB);
    music.play();
    music.setLoop(true);
    music.setVolume(10.f);

    //main menu
    mainMenu(window, music, audio, point);

    //snake's body variables
    Node body[10000];
    for (int i = 0; i < 10000; i++)
    {
        body[i].x = -20;
        body[i].y = -20;

    }
    body[0].x = 40;
    body[0].y = 80;

    //apple
    Node apple;
    apple.x = std::floor(rand() % 720 / 10) * 10 + 40;
    apple.y = std::floor(rand() % 680 / 10) * 10 + 80;

    //drawable objects
    sf::RectangleShape box;
    sf::CircleShape food(5.f);
    food.setFillColor(sf::Color::Red);
    food.setOrigin(5.f, 5.f);
    box.setSize(sf::Vector2f(10,10));

    //textures
    sf::Texture background;
    if (!background.loadFromFile("img/snake_background.png"))
        std::cout << "failed to load background texture!\n";
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(background);

    sf::Font font;
    if (!font.loadFromFile("batfont.ttf"))
        std::cout << "failed to load font!\n";
    sf::Text scoreT, timeT;
    scoreT.setFont(font);
    timeT.setFont(font);
    timeT.setPosition(140, 35);
    scoreT.setPosition(180, 0);

    

    //other variables
    int direction = 1, snakeLength = 10;
    sf::Clock deltaClock, gameTime;
    bool game = true,vertical = true, horizontal = false;
    int score = 0,temp;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();

            }
            //key mapping
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::W && direction != 2 && vertical)
            {
                vertical = false;
                horizontal = true;
                roundFunc(body, direction);
                direction = 0;
            }
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::D && direction != 3 && horizontal)
            {
                vertical = true;
                horizontal = false;
                roundFunc(body, direction);
                direction = 1;
            }
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::S && direction != 0 && vertical)
            {
                vertical = false;
                horizontal = true;  
                roundFunc(body, direction);
                direction = 2;
            }
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::A && direction != 1 && horizontal)
            {
                vertical = true;
                horizontal = false; 
                roundFunc(body, direction);
                direction = 3;
            }
            //if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::R && snakeLength < 10000)
               // snakeLength +=10;

        }
      
            
    
        if (game)
        {
            

            //the rest of the body follows head
            for (int i = snakeLength; i > 0; i--)
            {
                body[i].y = body[i - 1].y;
                body[i].x = body[i - 1].x;
            }
            //eating
            food.setPosition(apple.x, apple.y);
            eat(body, apple, snakeLength, score, point, audio);

            //moving function and delta time
            sf::Time dt = deltaClock.restart();
                move(body, direction, dt, game);

            if (gameTime.getElapsedTime().asSeconds() > 0.5)
                game = checkGame(body, snakeLength, direction, gameTime, game);
            
            temp = gameTime.getElapsedTime().asSeconds();

        }
        else
            gameOver(game, window, gameTime, body, snakeLength, score, direction, horizontal, vertical,deltaClock,point,audio);
        
        scoreT.setString(std::to_string(score));
        
        timeT.setString(std::to_string(temp));

        window.clear();
        //drawing objects
        window.draw(backgroundSprite);
        window.draw(timeT);
        window.draw(scoreT);
        window.draw(food);
        for (int i = 0; i < snakeLength; i++)
        {
            box.setPosition(body[i].x, body[i].y);
            window.draw(box);

        }
        
        

        window.display();
    }

    return 0;
}

