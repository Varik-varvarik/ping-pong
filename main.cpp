#include <SFML/Graphics.hpp>
using namespace sf;
class Game{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(Time);
    void render();
    void handlePlayerInput(Keyboard::Key, bool);

private:
    RenderWindow mWindow;
    RectangleShape  mPlayer;
    RectangleShape  mPlayerRight;
    CircleShape mBall;
    bool             mIsMovingUp,
            mIsMovingDown;
    bool             mIsMovingUp2,
            mIsMovingDown2;


    Time         TimePerFrame;
    float            PlayerSpeed;
    float            PlayerRightSpeed;
};

Game::Game()
        : mWindow(VideoMode(1000, 500), "Ping Pong")
        , mPlayer()
        , mPlayerRight()
        , PlayerSpeed(400.f)
        , PlayerRightSpeed(400.f)
{
    mPlayerRight.setSize(Vector2f(20, 100));
    mPlayerRight.setPosition(900.f, 100.f);
    mPlayerRight.setFillColor(Color(255, 0, 255));
    mPlayer.setSize(Vector2f(20, 100));
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(Color(255, 255, 255));
    mBall.setRadius((25.f));
    mBall.setPosition(2000.f/2, 500.f);
    mBall.setFillColor(Color(51, 255, 255));
    TimePerFrame = seconds(1.f / 120.f);
    mIsMovingUp = mIsMovingDown = false;
}

void Game::run() // game loop
{
    Clock clock;
    Time timeSinceLastUpdate = Time::Zero;
    while(mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type){
            case Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case Event::Closed:
                mWindow.close();
                break;
        }
    }
}


void Game::update(Time deltaTime)
{
    Vector2f movement(0.f, 0.f);
    Vector2f movement2(0.f, 0.f);
    if(mIsMovingUp)
        movement.y -= PlayerSpeed;
    else if(mIsMovingDown)
        movement.y += PlayerSpeed;
    else if(mIsMovingUp2)
        movement2.y -= PlayerRightSpeed;
    else if(mIsMovingDown2)
        movement2.y += PlayerRightSpeed;

    mPlayer.move(movement * deltaTime.asSeconds());
    mPlayerRight.move(movement2 * deltaTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.draw(mPlayerRight);
    mWindow.draw(mBall);
    mWindow.display();
}

void Game::handlePlayerInput(Keyboard::Key key, bool isPressed)
{
    if(key == Keyboard::W)
        mIsMovingUp = isPressed;
    else if(key == Keyboard::S)
        mIsMovingDown = isPressed;
    else if(key == Keyboard::Up)
        mIsMovingUp2 = isPressed;
    else if(key == Keyboard::Down)
        mIsMovingDown2 = isPressed;
}

int main()
{
    Game game;
    game.run();
}
