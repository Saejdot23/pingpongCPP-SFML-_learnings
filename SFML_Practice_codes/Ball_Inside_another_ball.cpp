#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <random>
using namespace std;
using namespace sf;
using Closed = Event::Closed;

void snapCondition(CircleShape& ball,float dx,float dy){
    float distance = sqrt(dx*dx + dy*dy);
    float overlap= (distance + 30) - 500;
    if(distance>0){
    ball.move({((-dx/distance)*overlap),((-dy/distance)*overlap)});
    }
    }

void CircularBallMotion(CircleShape& ball,float dx, float dy,Vector2f& vel){
   float distance = sqrt(dx*dx + dy*dy);
   float nx = dx/distance;
   float ny= dy/distance;

   float dot = ((vel.x*nx)+(vel.y*ny));
   vel.x= vel.x -(2*dot*nx);
   vel.y= vel.y -(2*dot*ny);
   vel*=0.95f;//energy lost
}
void ColorSwitch(CircleShape& ball,bool& flag){
    if(flag){
        ball.setFillColor(Color::Yellow);
        flag=false;
        }
        else{
            ball.setFillColor(Color::Red);
            flag=true;
        }
}
void ColorSwitch2(CircleShape& ball,bool& flag){
    if(flag){
        ball.setFillColor(Color::Cyan);
        flag=false;
        }
        else{
            ball.setFillColor(Color::White);
            flag=true;
        }
}
int main(){
    RenderWindow window (VideoMode({1920,1080}),"ping pong");//where y=0 is top and  y=1080 is bottom
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    CircleShape ball(30,100000);
    ball.setOrigin({30,30});
    ball.setPosition({500,500});
    ball.setFillColor(Color::Red);
    CircleShape ball2 (500,100000);
    ball2.setFillColor(Color::Black);
    ball2.setOutlineThickness(10);
    ball2.setOutlineColor(Color::White);
    ball2.setOrigin({500,500});
    ball2.setPosition({500,500});
    CircleShape ball3 (30,100000);
    ball3.setFillColor(Color::White);
    ball3.setOrigin({30,30});
    ball3.setPosition({250,250});
    float movespeed=6;
    float time=0;
    Vector2f velocity(movespeed,-movespeed);
    Vector2f velocity1(movespeed,-movespeed);
    velocity.x = 1.77f * movespeed;
    velocity.y = 1.0f * movespeed;
    velocity1.x = 1.77f * movespeed;
    velocity1.y = 1.0f * movespeed;
    bool flag1 =true,flag2=true;
    while(window.isOpen()){
    while(auto event = window.pollEvent()){
            if(event->is<Closed> () ){
                window.close();
            }
        }
    time=time+0.00001;
    ball.move(velocity);
    ball3.move(velocity1);
    velocity1.y+=(9.81*time);
    velocity.y+=(9.81*time);
    
    Vector2f centerPos = ball2.getPosition();
    Vector2f ballPos = ball.getPosition();
    float dx = ballPos.x - centerPos.x;
    float dy = ballPos.y - centerPos.y;
    float distance = sqrt(dx*dx + dy*dy);


    Vector2f ball3Pos = ball3.getPosition();
    float dx1 = ball3Pos.x - centerPos.x;
    float dy1= ball3Pos.y - centerPos.y;
    float dist = sqrt(dx1*dx1 + dy1*dy1);
    
    float bdx = ball3Pos.x - ballPos.x;
    float bdy = ball3Pos.y - ballPos.y;
    float DistanceBetweenBalls = sqrt(bdx*bdx + bdy*bdy);
    if(DistanceBetweenBalls <=(ball.getRadius()+ ball3.getRadius())){
        //snap condition
        float overlap = DistanceBetweenBalls - (ball.getRadius()+ ball3.getRadius());
        Vector2f normal ={bdx/DistanceBetweenBalls  , bdy/DistanceBetweenBalls};

        ball.move(normal*-overlap*0.5f);
        ball3.move(normal*overlap*0.5f);

        Vector2f relativeVelocity  = velocity - velocity1 ;
        float dot ((relativeVelocity.x*normal.x )+(relativeVelocity.y*normal.y));
        if(dot<0){
        Vector2f Impulse = dot * normal;
        velocity1+=Impulse;
        velocity-=Impulse;
        velocity*=0.95f;
        velocity1*=0.95f;
        }
    }
    if (dist +30 >=500){
        snapCondition(ball3,dx1,dy1);
        CircularBallMotion(ball3,dx1,dy1,velocity1);
        ColorSwitch2(ball3,flag2);
    }
    if (distance + 30 >= 500) {
        snapCondition(ball,dx,dy);
        CircularBallMotion(ball,dx,dy,velocity);
        ColorSwitch(ball,flag1);
    }
    window.clear(Color::Black);
    window.draw(ball2);
    window.draw(ball3);
    window.draw(ball);
    window.display();
    }
}
