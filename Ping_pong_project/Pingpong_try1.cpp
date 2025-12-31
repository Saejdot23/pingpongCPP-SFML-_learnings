#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <math.h>

using namespace sf;
using namespace std;
using Closed = Event::Closed;

class PauseManager{
    public:
    bool pauseFlag;
    float pausetimer;
    float pauseDuration;
    PauseManager(float pd){
        this->pauseDuration=pd;
        this->pauseFlag=false;
        this->pausetimer=0.0f;
    }
};
void MimicBall(RectangleShape& paddle,Vector2f& vel){
    paddle.setPosition({paddle.getPosition().x,paddle.getPosition().y + vel.y});
}
void UpdownWall(float up, float down ,CircleShape& b,Vector2f& vel){
    float posx=b.getPosition().x;
    float posy=b.getPosition().y;

    Vector2f position={posx,posy};
    Vector2f normal ={0.0f,0.0f};
    if(posy<b.getRadius()){//upcase
        b.setPosition({b.getPosition().x,b.getRadius()});
        normal={0.0f,1.0f};
        float dot = (normal.x * vel.x)+(normal.y* vel.y);
        vel-=(2*dot*normal);
    }
    else if(posy>down-b.getRadius()){//downcase
        b.setPosition({b.getPosition().x,down - b.getRadius()});
        normal={0.0f,-1.0f};
        float dot = (normal.x * vel.x)+(normal.y* vel.y);
        vel-=(2*dot*normal);
    }
}

bool PaddleBallCollisionR(RectangleShape& paddle,CircleShape& ball,Vector2f& vel,Vector2f dim){   
    Vector2f PaddlePos =paddle.getPosition();//gives origin 
    Vector2f BallPos = ball.getPosition();
    Vector2f DistanceVector = PaddlePos - BallPos;
    float DistanceFromPaddleCenter = sqrt(pow(DistanceVector.x,2) + pow(DistanceVector.y,2));
    float CollisionCirlceRadius = (0.05f * (sqrt(pow(dim.x,2)+ pow(dim.y,2))) ) + ball.getRadius();
    
    if(DistanceFromPaddleCenter<=CollisionCirlceRadius){
        if(BallPos.x >= PaddlePos.x-(dim.x/2)){
            float overlap = BallPos.x - (PaddlePos.x-(dim.x/2));
            ball.setPosition({ball.getPosition().x-overlap , ball.getPosition().y});

            Vector2f normal = {-1.0f,0.0f};

            float dot = (normal.x*vel.x)+(normal.y*vel.y);
            
            vel-=(2*dot*normal);
            return true;
        }
    }

    return false;
}

bool PaddleBallCollisionL(RectangleShape& paddle,CircleShape& ball,Vector2f& vel,Vector2f dim){   
    Vector2f PaddlePos =paddle.getPosition();//gives origin 
    Vector2f BallPos = ball.getPosition();
    Vector2f DistanceVector = PaddlePos - BallPos;
    float DistanceFromPaddleCenter = (sqrt(pow(DistanceVector.x,2) + pow(DistanceVector.y,2)));
    float CollisionCirlceRadius = (0.05f * (sqrt(pow(dim.x,2)+ pow(dim.y,2))) ) + ball.getRadius();
    
    if(DistanceFromPaddleCenter<=CollisionCirlceRadius){
        if(BallPos.x <= PaddlePos.x+(dim.x/2)){
            float overlap = abs(BallPos.x - (PaddlePos.x+(dim.x/2)));
            ball.setPosition({ball.getPosition().x+overlap , ball.getPosition().y});

            Vector2f normal = {1.0f,0.0f};

            float dot = (normal.x*vel.x)+(normal.y*vel.y);
            
            vel-=(2*dot*normal);
            return true;
        }
    }

    return false;
}

bool BallCrossedWithoutPaddleL(CircleShape& ball,Vector2f dim){
    if(ball.getPosition().x <= 0.0f){
        ball.setPosition({0.0f,ball.getPosition().y});
        return true;
    }
    return false;
}

int main(){
    RenderWindow window(VideoMode({1920,1080}),"Marty Supreme");
    window.setFramerateLimit(144);
    float up=0.0f;
    float down=window.getSize().y;

    Vector2f vel ={11.0f,-4.0f};
    Vector2f StartingVel={11.0f,-4.0f};
    CircleShape ball(30.0f,60);
    ball.setFillColor(Color::Red);
    ball.setOrigin({ball.getRadius(),ball.getRadius()});
    ball.setPosition({window.getSize().x/2.0f , window.getSize().y/2.0f});

    Font font ;
    if(!font.openFromFile("arial.ttf")){
        return -1;
    }

    Text GO(font);
    GO.setString("GAME OVER");
    GO.setCharacterSize(50.0f);
    GO.setStyle(Text::Bold);
    GO.setFillColor(Color::Red);
    FloatRect TextDim = GO.getLocalBounds();
    GO.setOrigin({TextDim.position.x + TextDim.size.x / 2.0f, TextDim.position.y + TextDim.size.y / 2.0f});
    GO.setPosition({960.0f, 540.0f});

    Vector2f PaddleSpeed={0.0f,0.0f};
    Vector2f Dimensions={50.0f,100.0f};
    RectangleShape PaddleL(Dimensions);
    PaddleL.setFillColor(Color::White);
    PaddleL.setOrigin({Dimensions.x/2,Dimensions.y/2});
    PaddleL.setPosition({Dimensions.x/2,window.getSize().y/2.0f});

    RectangleShape PaddleR(Dimensions);
    PaddleR.setFillColor(Color::White);
    PaddleR.setOrigin({Dimensions.x/2,Dimensions.y/2});
    PaddleR.setPosition({1920.0f-(Dimensions.x/2) ,(1080.0f/2.0f)});

    PauseManager Gameover(144.0f*3);
    float deltaT=1.0f;
    //game loop
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Closed> ()){
                window.close();
            }
        }
        if(BallCrossedWithoutPaddleL(ball,Dimensions)){
            window.clear(Color::Black);
            window.draw(ball);
            window.draw(PaddleL);
            window.draw(PaddleR);
            window.draw(GO);
            window.display();
            Gameover.pausetimer+=deltaT;
            if(Gameover.pausetimer >= Gameover.pauseDuration){
                ball.setPosition({window.getSize().x/2.0f , window.getSize().y/2.0f});
                Gameover.pausetimer=0;
                vel = StartingVel;
                PaddleR.setPosition({1920.0f-(Dimensions.x/2) ,(1080.0f/2.0f)});
            }
        }
        else{
        
        if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
            PaddleSpeed={0.0f,-10.0f};
            PaddleL.move(PaddleSpeed);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
            PaddleSpeed={0.0f,10.0f} ;
            PaddleL.move(PaddleSpeed);
        }

        UpdownWall(up,down,ball,vel);
        MimicBall(PaddleR,vel);
        PaddleBallCollisionR(PaddleR,ball,vel,Dimensions);
        PaddleBallCollisionL(PaddleL,ball,vel,Dimensions);
        ball.move(vel);
        window.clear(Color::Black);
        window.draw(ball);
        window.draw(PaddleL);
        window.draw(PaddleR);
        window.display();
        }
        
    }
}
