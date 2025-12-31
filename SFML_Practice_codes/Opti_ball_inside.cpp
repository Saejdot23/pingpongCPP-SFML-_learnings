#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <random>
using namespace std;
using namespace sf;
using Closed = Event::Closed;

int main(){
    RenderWindow window (VideoMode({1920,1080}),"ping pong");//where y=0 is top and  y=1080 is bottom
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    CircleShape ball(30,100000);
    CircleShape ball2 (500,100000);
    CircleShape ball3 (30,100000);
    ball2.setFillColor(Color::Black);
    ball2.setOutlineThickness(10);
    ball2.setOutlineColor(Color::White);
    ball2.setOrigin({500,500});
    ball2.setPosition({500,500});
    ball.setOrigin({30,30});
    ball.setPosition({500,500});
    ball.setFillColor(Color::Red);
    float movespeed=900.0f;
    float time=0;
    Vector2f velocity(movespeed,-movespeed);
    velocity.x = 1.77f * movespeed;
    velocity.y = 1.0f * movespeed;
    Clock clock;
    bool flag =true;
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Closed> () ){
                window.close();
            }
        }
       Time dt = clock.restart();
    float deltaTime = dt.asSeconds();

    // 3. MOVE BASED ON REAL TIME
    // This ensures the ball moves the same distance per SECOND, 
    // regardless of how fast the frames are.
    ball.move(velocity * deltaTime); 
    
    // Apply your gravity logic here...
    velocity.y += (981.0f * deltaTime);
    Vector2f ballPos = ball.getPosition();
    Vector2f centerPos = ball2.getPosition();

    float dx = ballPos.x - centerPos.x;
    float dy = ballPos.y - centerPos.y;
    float distance = sqrt(dx*dx + dy*dy);

    if (distance + 30 >= 500) {
        float overlap = (distance + 30) - 500;
        if (distance > 0) {
        ball.move({
            -(dx / distance) * overlap,
            -(dy / distance) * overlap
        });
        }//snap condition

        float nx = dx/distance;
        float ny = dy/distance;

        float dot = ((nx*velocity.x) + (ny*velocity.y));

        velocity.x=velocity.x - (2* dot * nx);
        velocity.y=velocity.y - (2* dot *ny) + (9.81*time);
        if(flag){
        ball.setFillColor(Color::Yellow);
        flag=false;
        }
        else{
            ball.setFillColor(Color::Red);
            flag=true;
        }
    }
    window.clear(Color::Black);
    window.draw(ball2);
    window.draw(ball);
    window.display();
    
    }
}
