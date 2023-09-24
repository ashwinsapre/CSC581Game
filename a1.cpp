#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Time.h"

class Game{
public:
    float movingSurfacexvel = 0.2;
    float friction = 0.99;
    float gravity = 1;
    float maxVel = 2;
    float aspectRatio = 8.0/6.0;
    float speed = 10;
    float jumpSpeed = 150;

    float _ballDim = 30.f;
    float _surfaceDimX = 500.f;
    float _surfaceDimY = 10.f;
    float _surfaceLevel = 400.f;
    float _initBallX = 50.f;
    float _initBallY = 100.f;
    float _movingSurfaceDimX = 200.f;
    float _movingSurfaceDimY = 10.f;
    float _movingSurfaceVel = 0.5f;
    sf::RenderWindow window;
    float _windowLength = 800;
    float _windowHeight =  600;

    bool isProportional;
    bool inTheAir;

    Time *time = new Time();
    Circle *ball = new Circle();
    Rectangle *surface = new Rectangle();
    Rectangle *movingSurface = new Rectangle();
    Rectangle *Lwall = new Rectangle();
    Rectangle *Rwall = new Rectangle();
    Rectangle *Uwall = new Rectangle();
    sf::Texture *ballTexture = new sf::Texture;
    sf::Texture *surfaceTexture= new sf::Texture;

    Game(){}

    void init(){
        window.create(sf::VideoMode(_windowLength, _windowHeight), "Assignment 1", sf::Style::Default);
        isProportional = false;
        ballTexture->loadFromFile("ball.png");
        surfaceTexture->loadFromFile("brick_wall.png");

        ball->init(_ballDim, 50.f, 100.f);
        surface->init(_surfaceDimX, _surfaceDimY, 0.f, _surfaceLevel);
        movingSurface->init(_movingSurfaceDimX, _movingSurfaceDimY, 550.f, _surfaceLevel);
        Lwall->init(10, _surfaceLevel, 0, 0);
        Rwall->init(10, _surfaceLevel, 790, 0);
        Uwall->init(800, 10, 0, 0);

        ball->setTexture(ballTexture);
        surface->setTexture(surfaceTexture);
        movingSurface->setTexture(surfaceTexture);
        Lwall->setTexture(surfaceTexture);
        Rwall->setTexture(surfaceTexture);
        Uwall->setTexture(surfaceTexture);

        inTheAir = true;
    }
    void shutdown(){
        delete ball;
        delete surface;
        delete movingSurface;
        delete Lwall;
        delete Uwall;
        delete Rwall;
    }
};


void HIDS(Game *game, sf::Event event){
    if (event.type == sf::Event::Closed)
        game->window.close();
    
    if (event.type == sf::Event::Resized){
        float newwidth = event.size.width;
        float newheight = event.size.height;

        //constant size of game shapes
        if (game->isProportional == false){
            sf::FloatRect newWindow(0,0,newwidth, newheight);
            game->window.setView(sf::View(newWindow));
        }

        //default, proportional scaling
        else{
            sf::FloatRect newWindow(0,0,game->_windowLength, game->_windowHeight);
            game->window.setView(sf::View(newWindow));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        game->isProportional = !game->isProportional;
        float newwidth = event.size.width;
        float newheight = event.size.height;

        //constant size of game shapes
        if (game->isProportional == false){
            sf::FloatRect newWindow(0,0,newwidth, newheight);
            game->window.setView(sf::View(newWindow));
        }
        //default, proportional scaling
        else{
            sf::FloatRect newWindow(0,0,game->_windowLength, game->_windowHeight);
            game->window.setView(sf::View(newWindow));
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        game->ball->move(game->speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        game->ball->move(-game->speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        game->ball->move(0, -game->jumpSpeed);
    }
}

void movementService(Game *game){
    //ball movement
    if (game->inTheAir == false){
        game->ball->move(0, 0);
    }
    else{
        game->ball->move(0, game->gravity);
    }

    //reset ball position
    if (game->ball->getPosition().y > game->_windowHeight){
        game->ball->setPosition(game->_initBallX, game->_initBallY);
        game->inTheAir = true;
    }


    //moving surface movement
    if (game->movingSurface->getPosition().x > 700 || game->movingSurface->getPosition().x < 500){
        game->_movingSurfaceVel *= -1;
    }
    game->movingSurface->setPosition(game->movingSurface->getPosition().x + game->_movingSurfaceVel, game->movingSurface->getPosition().y);

}

void collisionService(Game *game){

        //get bounding boxes
        sf::FloatRect surfaceBB(game->surface->getBoundingBox());
        sf::FloatRect movingSurfaceBB(game->movingSurface->getBoundingBox());
        sf::FloatRect ballBB(game->ball->getBoundingBox());
        sf::FloatRect LWallBB(game->Lwall->getBoundingBox());
        sf::FloatRect RWallBB(game->Rwall->getBoundingBox());
        sf::FloatRect UWallBB(game->Uwall->getBoundingBox());

        //ball with surfaces
        if ((ballBB.intersects(movingSurfaceBB) || ballBB.intersects(surfaceBB)) && game->ball->getPosition().y < game->_surfaceLevel - game->_ballDim){
            game->inTheAir = false;
        }
        else{
            game->inTheAir = true;
        }

        if (ballBB.intersects(movingSurfaceBB)){
            game->ball->move(game->_movingSurfaceVel, 0);
        }


        //collisions with game boundaries
        if (ballBB.intersects(LWallBB)){
                game->ball->move(1, 0);
        }
        if (ballBB.intersects(RWallBB)){
                game->ball->move(-1, 0);
        }
        if (ballBB.intersects(UWallBB)){
                game->ball->move(0, 1);
        }

  
}

void renderService(Game *game){
    game->window.clear();
    game->window.draw(*game->surface);
    game->window.draw(*game->movingSurface);
    game->window.draw(*game->ball);
    game->window.draw(*game->Lwall);
    game->window.draw(*game->Uwall);
    game->window.draw(*game->Rwall);
    game->window.display();
}

int main()
{
    static Game *game = new Game();
    game->init();

    //START GAME LOOP
    while (game->window.isOpen())
    {
        sf::Event event;

        //human input detection
        while (game->window.pollEvent(event))
        {

            HIDS(game, event);
        }
        //movement service
        movementService(game);

        //collision service
        collisionService(game);

        //rendering service
        renderService(game);
        game->time->next_time();

    }

    //cleanup service
    game->shutdown();
    delete game;

    return 0;
}