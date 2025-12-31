#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
using Closed = Event::Closed;
int main(){
    RenderWindow window (VideoMode({1920,1080}),"ball");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    CircleShape ball(30,100000);
    ball.setPosition({500,500});
    ball.setFillColor(Color::Red);
    float movespeed =12;
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Closed> () ){
                window.close();
            }
        }
            if(Keyboard::isKeyPressed(Keyboard::Key::Left)){
            if(ball.getPosition().x<0){
                ball.setFillColor(Color::Red);
                continue;
            }    
            else{
            ball.move({-movespeed,0});
            }
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Right)){
            if(ball.getPosition().x>1920-(ball.getRadius()*2)){
                ball.setFillColor(Color::Green);
                continue;
            } 
            else{
            ball.move({movespeed,0});
            }
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
                if(ball.getPosition().y<0){
                    ball.setFillColor(Color::Yellow);
                    continue;
                }
                else{
            ball.move({0,-movespeed});
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Down)){

            if(ball.getPosition().y>1080-(ball.getRadius()*2)){
                    ball.setFillColor(Color::White);
                    continue;
                }
                else{
            ball.move({0,movespeed});
                }
            }
    
    window.clear(Color::Black);
    window.draw(ball);
    window.display();
    }
}
