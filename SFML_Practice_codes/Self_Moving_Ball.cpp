#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
using Closed = Event::Closed;
int main(){
    RenderWindow window (VideoMode({1920,1080}),"ping pong");//where y=0 is top and  y=1080 is bottom
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    CircleShape ball(30,100000);
    CircleShape ball2 (500,100000);
    ball2.setFillColor(Color::Black);
    ball2.setOutlineThickness(10);
    ball2.setOutlineColor(Color::White);
    ball2.setOrigin({500,500});
    ball2.setPosition({500,500});
    ball.setOrigin({30,30});
    ball.setPosition({500,500});
    ball.setFillColor(Color::Red);
    float movespeed=12;
    Vector2f velocity(movespeed,-movespeed);
    velocity.x = 1.77f * movespeed;
    velocity.y = 1.0f * movespeed;
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Closed> () ){
                window.close();
            }
        }
    ball.move(velocity) ;//launched at 20*root2 45 degree angle
    if(ball.getPosition().y<0){
        ball.setFillColor(Color::Blue);
        velocity.y=-velocity.y;
    }
    if(ball.getPosition().x>1920-(ball.getRadius()*2)){
        ball.setFillColor(Color::Yellow);
        velocity.x=-velocity.x;
    }
    if(ball.getPosition().y>1080-(ball.getRadius()*2)){
        ball.setFillColor(Color::Green);
        velocity.y=-velocity.y;
    }
    if(ball.getPosition().x<0){
        ball.setFillColor(Color::Red);
        velocity.x=-velocity.x;
    }
    window.clear(Color::Black);
    window.draw(ball);
    window.display();
    
    }
}
