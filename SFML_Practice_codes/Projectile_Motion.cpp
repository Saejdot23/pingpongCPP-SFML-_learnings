#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <math.h>
#include <iostream>
using namespace sf;
using Closed = Event::Closed ;


int main(){
    RenderWindow window(VideoMode({1920,1080}),"Projectile");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    RectangleShape ground(Vector2f(1920.0f, 1080.0f / 3.0f));
    ground.setOrigin(Vector2f(0.f, 0.f));
    ground.setPosition(Vector2f(0.f, (2.f * 1080.0f) / 3.0f));
    ground.setFillColor(Color::Green);

    CircleShape ball(30,60);
    ball.setOrigin({30,30});
    ball.setPosition({ball.getRadius(),(((2.f * 1080.0f) / 3.0f)-ball.getRadius())});
    ball.setFillColor(Color::Red);
    float moveSpeed=13;
    Vector2f VelLaunch(moveSpeed,-moveSpeed);
    float timeElapsed =0;
    float timeKeeper=0;

    RectangleShape target({120.0f,120.0f});
    target.setOrigin({60.0f,60.0f});
    target.setFillColor({Color::White});
    target.setPosition({900,400});
    target.setRotation(sf::degrees(0.0f));
    
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Closed> ()){
                window.close();
            }
        }
        target.rotate(sf::degrees(0.5f));
        Vector2f ballPos=ball.getPosition();
        Vector2f FututreBallPos = ballPos + VelLaunch ;
        timeElapsed+=0.005f;
        
        float deltaTime=0.005f;
        VelLaunch.y+=(9.81*deltaTime);//gravity

        Vector2f reactanglePos =target.getPosition();

        float dx = FututreBallPos.x - reactanglePos.x;
        float dy = FututreBallPos.y - reactanglePos.y;

        float distance = sqrt(dx*dx  + dy*dy);

        float CornerHit = (0.5*sqrt(120*120 + 120*120) )+ball.getRadius();

        float FaceUphit = 30 + ball.getRadius();
        float DownHit = 30 + ball.getRadius();

        if(timeElapsed>0){
        if(distance < CornerHit){
            float overlap = CornerHit - distance;
            Vector2f normal1= {dx/distance,dy/distance};
            ball.setPosition(ballPos + (normal1 * overlap));//setpostion instead of move 
            float dot = (normal1.x * VelLaunch.x) + (normal1.y* VelLaunch.y);
            if(dot<0){
            VelLaunch = VelLaunch - (2*dot*normal1);
            }
            target.setFillColor(Color::Yellow);
            timeKeeper = timeElapsed ;
        }


        if(ballPos.y>(((2.f * 1080.0f) / 3.0f)-ball.getRadius())){
            VelLaunch.y=-VelLaunch.y;
            VelLaunch*=0.95f;
        }
        if(ballPos.y<0){
            VelLaunch.y=-VelLaunch.y;
            VelLaunch*=0.95f;
            ball.setPosition({ball.getPosition().x,0});
        }
        if(ballPos.x>(1920-ball.getRadius())){
            VelLaunch.x=-VelLaunch.x;
            ball.setPosition({1920-ball.getRadius(),ball.getPosition().y});
        }
        if(ballPos.x<ball.getRadius()){
            VelLaunch.x=-VelLaunch.x;
            ball.setPosition({ball.getRadius(),ball.getPosition().y});
        }
        if(timeElapsed - timeKeeper >= 0.5){
            timeKeeper = timeElapsed ;
            target.setFillColor(Color::White);
        }
        ball.move(VelLaunch);
    }
        window.clear(Color::Black);
        window.draw(ground);
        window.draw(ball);
        window.draw(target);
        window.display();
    }
    
}
